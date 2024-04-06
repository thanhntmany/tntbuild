#include <sys/uio.h>  // iovec, preadv
#include <stdio.h>    //SEEK_SET
#include <fcntl.h>    // open, F_WRLCK, F_UNLCK, F_SETLK
#include <sys/stat.h> // S_IRUSR, S_IWUSR
#include <stdlib.h>   // malloc, free, alloca
#include <string.h>   // memcpy
#include "sbufio.h"

/**************************************
 * I/O with file descriptor by page.
 */

int read_page(int fd, off_t offset, void *const restrict buf, size_t page_size)
{
    struct iovec iov = {.iov_len = page_size, .iov_base = buf};
    return preadv(fd, &iov, 1, offset); // #TODO: Error handling
};

int write_page(int fd, off_t offset, void *const restrict buf, size_t page_size)
{
    struct iovec iov = {.iov_len = page_size, .iov_base = buf};
    return pwritev(fd, &iov, 1, offset); // #TODO: Error handling
};

/**************************************
 * sbufio_db
 */

/* db_page_* */

static struct sbufio_db_page *db_page_open(struct sbufio_db *const restrict db, const off_t offset)
{
    struct sbufio_db_page *page = malloc(sizeof(struct sbufio_db_page));
    const size_t page_size = db->_page_size;

    read_page(
        db->fd,
        page->offset = offset,
        page->buf = memalign(page_size, page_size),
        page_size);

    page->changed = false;
    return page;
};

static void db_page_close(struct sbufio_db *const restrict db, struct sbufio_db_page *const restrict page)
{
    if (page->changed)
        write_page(
            db->fd,
            page->offset,
            page->buf,
            db->_page_size);
    free(page->buf);
    free(page);
};

/* db_locate_* */

static off_t db_locate_offset(struct sbufio_db *const restrict db, const off_t offset, struct sbufio_db_page **const found_page)
{
    const off_t p_offset = offset % db->_page_size, page_offset = offset - p_offset;
    struct sbufio_db_page *restrict page = db->anchor_page.next;
    if (page->offset != page_offset) // if not first page
    {
        register off_t o;
        while ((o = (page = page->next)->offset) != page_offset)
            if (o < 0)
            {
                page = db_page_open(db, page_offset);
                goto retpage;
            };
        (page->prev->next = page->next)->prev = page->prev;

    retpage:
        (((page->next = db->anchor_page.next)->prev = page)->prev = &db->anchor_page)->next = page; // move page to the first position
    };

    *found_page = page;
    return p_offset;
};

static off_t db_locate_sb(struct sbufio_db *const restrict db, struct sbuf *sb, struct sbufio_db_page **const found_page)
{
    const size_t page_size = db->_page_size;
    off_t p_offset;
    struct sbufio_db_page *restrict page = db->anchor_page.next;

    if ((p_offset = sb - page->buf) < 0 || p_offset >= page_size) // if not first page
    {
        while ((p_offset = sb - (page = page->next)->buf) < 0 || p_offset >= page_size)
            if (!page->buf)
            {
                *found_page = NULL;
                return -1;
            };

        (page->prev->next = page->next)->prev = page->prev;
        (((page->next = db->anchor_page.next)->prev = page)->prev = &db->anchor_page)->next = page; // move page to the first position
    };

    *found_page = page;
    return p_offset;
};

/* db_* I/O */

static void db_write(struct sbufio_db *const restrict db, off_t offset, void *restrict buf, size_t nbyte)
{
    const off_t page_size = db->_page_size;
    struct sbufio_db_page *page;
    off_t p_offset;
    size_t load;
    while (nbyte)
    {
        p_offset = db_locate_offset(db, offset, &page);
        if ((load = page_size - p_offset) > nbyte)
            load = nbyte;
        page->changed = true;
        memcpy(page->buf + p_offset, buf, load);
        offset += load;
        buf += load;
        nbyte -= load;
    };
};

static void db_read(struct sbufio_db *const restrict db, off_t offset, void *restrict buf, size_t nbyte)
{
    const off_t page_size = db->_page_size;
    struct sbufio_db_page *page;
    off_t p_offset;
    size_t load;
    while (nbyte)
    {
        p_offset = db_locate_offset(db, offset, &page);
        if ((load = page_size - p_offset) > nbyte)
            load = nbyte;
        memcpy(buf, page->buf + p_offset, load);
        offset += load;
        buf += load;
        nbyte -= load;
    };
};

/* db_sb_* I/O */

static off_t db_sb_alloc(struct sbufio_db *const restrict db, off_t size){
    // #TODO: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
};

static void db_sb_free(struct sbufio_db *const restrict db, off_t offset)
{
    if (offset <= 0)
        return;

    struct sbuf_header h;
    db_read(db, offset, &h, sizeof(h));
    h.used = db->sb0->h.used;
    db_write(db, offset, &h, sizeof(h));

    db->sb0->h.used = -offset;
};

/* db_* */

static const struct flock const DB_FLOCK = {.l_whence = SEEK_SET, .l_start = 0, .l_len = 0};

static struct sbufio_db *db_open(const char *const restrict filename)
{
    // Init handler
    struct sbufio_db *const restrict db = malloc(sizeof(struct sbufio_db));
    db->fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    // Init lock, lock write (+read)
    db->flock = DB_FLOCK;
    db->flock.l_type = F_WRLCK;
    fcntl(db->fd, F_SETLKW, &db->flock);

    struct stat st;
    fstat(db->fd, &st); // #TODO: error handling
    const long st_blksize = st.st_blksize;
    size_t b = 512;
    while (b < st_blksize)
        b <<= 1;
    db->_page_size = b;
    db->anchor_page.offset = -1;
    db->anchor_page.next = db->anchor_page.prev = &db->anchor_page;

    // Metadata segment (offset = 0)
    struct sbufio_db_page *d0_page;
    struct sbufio_sb0 *sb0 = db->sb0 = db_locate_offset(db, 0, &d0_page) + d0_page->buf;

    // #TODO: xxxxx
    sb0->h.size = sb0->h.used = sizeof(*sb0) - sizeof(sb0->h);

    return db;
};

static void db_close(struct sbufio_db *const restrict db)
{
    struct sbufio_db_page *db_page;
    while ((db_page = db_page->next)->buf)
        db_page_close(db, db_page);
    db->anchor_page.next = db->anchor_page.prev = &db->anchor_page;

    db->flock.l_type = F_UNLCK;
    fcntl(db->fd, F_SETLKW, &db->flock);
    close(db->fd);
    free(db);
};

static void *db_sbuf_free(struct sbufio_db *const restrict db, off_t offset)
{
    struct sbuf_header h;
    db_read(db, offset, &h, sizeof(h));
    h.used = 0;
    db_write(db, offset, &h, sizeof(h));
};

static off_t db_sbuf_alloc(struct sbufio_db *const restrict db, const off_t size)
{
    off_t offset = db->sb0->next_offset;
    struct sbuf_header h;
    db_read(db, offset, &h, sizeof(h));
    h.used = 0;
    h.size = size;
    db_write(db, offset, &h, sizeof(h));
    db->sb0->next_offset = offset + size + sizeof(h);
    return offset;
};

static struct sbuf *db_sbuf_get(struct sbufio_db *const restrict db, off_t offset)
{
    struct sbuf_header h;
    db_read(db, offset, &h, sizeof(h));
    if (h.size <= 0)
        return NULL;

    struct sbuf *sb = sbuf_init();
    memcpy(&sb->h, &h, sizeof(struct sbuf_header));
    db_read(db, offset + sizeof(struct sbuf_header), sb->buf = malloc(sb->h.size), sb->h.used);
    return sb;
};

/* return the db_offset of stored segbuf */
static off_t db_sbuf_flush(struct sbufio_db *const restrict db, off_t offset, struct sbuf *const restrict sb)
{
    struct sbuf_header h;
    struct sbufio_db_page *page;
    off_t p_offset = db_locate_offset(db, offset, &page);

    db_read(db, offset, &h, sizeof(struct sbuf_header));
    if (h.size >= sb->h.used)
    {
        h.used = sb->h.used;
    }
    else
    {
        db_sbuf_free(db, offset);
        offset = db_sbuf_alloc(db, sb->h.used);
        h.size = h.used = sb->h.used;
    };

    db_write(db, offset, &h, sizeof(struct sbuf_header));
    db_write(db, offset + sizeof(h), sb->buf, h.used);
    return offset;
};

/**************************************
 * sbufio_idx
 */

static char _FREED_SBUF;
static const struct sbuf *const restrict FREED_SBUF = &_FREED_SBUF;

/* idx_page_* */

struct sbufio_idx_page *idx_page_open(struct sbufio_idx *const restrict idx, off_t offset)
{
    struct sbufio_idx_page *page = malloc(sizeof(struct sbufio_idx_page));
    const size_t page_size = idx->_page_size;

    read_page(
        idx->fd,
        page->offset = offset,
        page->buf = memalign(page_size, page_size),
        page_size);

    page->sbs = memalign(page_size, page_size),
    memset(page->sbs, 0, page_size);

    page->nref = 0;
    return page;
};

void idx_page_close(struct sbufio_idx *const restrict idx, struct sbufio_idx_page *page)
{
    write_page(
        idx->fd,
        page->offset,
        page->buf,
        idx->_page_size);
    page->changed = false;

    free(page->buf);
    free(page->sbs);
    free(page);
};

/* idx_locate_* */

static off_t idx_locate_id(struct sbufio_idx *const restrict idx, const off_t id, struct sbufio_idx_page **const found_page)
{
    const off_t offset = id * sizeof(off_t), p_offset = offset % idx->_page_size, page_offset = offset - p_offset;
    struct sbufio_idx_page *restrict page = idx->anchor_page.next;
    if (page->offset != page_offset) // if not first page
    {
        register off_t o;
        while ((o = (page = page->next)->offset) != page_offset)
            if (o < 0)
            {
                page = idx_page_open(idx, page_offset);
                goto retpage;
            };
        (page->prev->next = page->next)->prev = page->prev;

    retpage:
        (((page->next = idx->anchor_page.next)->prev = page)->prev = &idx->anchor_page)->next = page; // move page to the first position
    };

    *found_page = page;
    return p_offset;
};

static off_t idx_locate_sb(struct sbufio_idx *const restrict idx, struct sbuf *sb, struct sbufio_idx_page **const found_page)
{
    size_t page_size = idx->_page_size;
    struct sbufio_idx_page *restrict page = idx->anchor_page.next;
    off_t p_offset;

    if ((p_offset = sb - page->buf) < 0 || p_offset >= page_size) // if not first page
    {
        while ((p_offset = sb - (page = page->next)->buf) < 0 || p_offset >= page_size)
            if (!page->buf)
            {
                *found_page = NULL;
                return -1;
            };
        (page->prev->next = page->next)->prev = page->prev;
        (((page->next = idx->anchor_page.next)->prev = page)->prev = &idx->anchor_page)->next = page; // move page to the first position
    };

    *found_page = page;
    return p_offset;
};

static const struct flock const IDX_FLOCK = {.l_whence = SEEK_SET, .l_start = 0, .l_len = 0};

static struct sbufio_idx *idx_open(const char *const restrict filename)
{
    // Init handler
    struct sbufio_idx *const restrict idx = malloc(sizeof(struct sbufio_idx));
    idx->fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    // Init lock, lock write (+read)
    idx->flock = IDX_FLOCK;
    idx->flock.l_type = F_WRLCK;
    fcntl(idx->fd, F_SETLKW, &idx->flock);

    struct stat st;
    fstat(idx->fd, &st); // #TODO: error handling
    const long st_blksize = st.st_blksize;
    size_t b = 512;
    while (b < st_blksize)
        b <<= 1;
    idx->_page_size = b;
    idx->anchor_page.offset = -1;
    idx->anchor_page.next = idx->anchor_page.prev = &idx->anchor_page;

    // Lowest Available ID
    struct sbufio_idx_page *i0_page;
    idx->i0 = idx_locate_id(idx, 0, &i0_page) + i0_page->buf;
    if (-idx->i0->_tail_id < sizeof(idx->i0) / sizeof(off_t))
        idx->i0->_tail_id = -sizeof(idx->i0) / sizeof(off_t);

    i0_page->nref = 1;
    i0_page->changed = true;

    return idx;
};

static void idx_close(struct sbufio_idx *const restrict idx)
{
    idx->flock.l_type = F_UNLCK;
    fcntl(idx->fd, F_SETLKW, &idx->flock);
    close(idx->fd);
    free(idx);
};

static void idx_buf_free(struct sbufio_idx *const restrict idx, const off_t p_offset, struct sbufio_idx_page *page)
{
    // page->changed = true;
    off_t *id_buf_p = page->buf + p_offset;
    if (*id_buf_p < 0)
        return;

    struct sbufio_idx_page *idx_page;
    off_t *tail_id_p = idx_locate_id(idx, -idx->i0->_tail_id, &idx_page) + idx_page->buf;

    *id_buf_p = *tail_id_p;
    *tail_id_p = -(page->offset + p_offset) / sizeof(off_t);
};

static void idx_buf_setnone(struct sbufio_idx *const restrict idx, const off_t p_offset, struct sbufio_idx_page *page)
{
    // page->changed = true;
    off_t *id_buf_p = page->buf + p_offset;
    off_t id_buf = *id_buf_p;
    if (id_buf < 0)
    {
        off_t _cur_id = -(page->offset + p_offset) / sizeof(off_t);
        struct sbufio_idx_page *i_page;
        off_t *_i_p = idx_locate_id(idx, -idx->i0->_tail_id, &i_page) + i_page->buf;
        off_t _i = *_i_p;
        while (_i != _cur_id)
        {
            _i_p = idx_locate_id(idx, -_i, &i_page) + i_page->buf;
            _i = *_i_p;
            if (_i >= 0)
                goto ret;
        };

        *_i_p = id_buf;
    };
ret:
    *id_buf_p = 0;
};

static off_t idx_buf_available(struct sbufio_idx *const restrict idx)
{
    struct sbufio_idx_page *i_page;
    off_t id = -idx->i0->_tail_id;
    off_t _i = *(off_t *)(idx_locate_id(idx, id, &i_page) + i_page->buf);

    while (_i > 0)
        _i = *(off_t *)(idx_locate_id(idx, ++id, &i_page) + i_page->buf);

    if (_i == 0)
        idx->i0->_tail_id = -id;

    return id;
};

static void idx_free(struct sbufio_idx *const restrict idx, const off_t p_offset, struct sbufio_idx_page *page)
{
    struct sbuf **id_sb_p = page->sbs + p_offset;
    struct sbuf *sb = *id_sb_p;

    if (!sb || sb == FREED_SBUF)
        return;

    page->changed = true;
    // sbs
    sbuf_free(sb);
    *id_sb_p = FREED_SBUF;
    ++page->nref;
    // buf
    idx_buf_free(idx, p_offset, page);
};

static void idx_set(struct sbufio_idx *const restrict idx, const off_t p_offset, struct sbufio_idx_page *page, struct sbuf *sb)
{
    if (!sb)
    {
        idx_free(idx, p_offset, page);
        return;
    };

    page->changed = true;
    // sbs
    *(struct sbuf **)(page->sbs + p_offset) = sb;
    ++page->nref;
    // buf
    idx_buf_setnone(idx, p_offset, page);
};

/**************************************
 * sbufio
 */

static char *IDX_SUFFIX = ".idx";
static void sbufio_flush(struct sbufio *const restrict sbio)
{
    struct sbufio_idx *idx = sbio->idx;
    struct sbufio_idx_page *page = &idx->anchor_page, *page_next;
    off_t p_offset;
    const page_size = idx->_page_size;
    void *sbs;
    off_t *buf;
    off_t db_offset;
    struct sbuf *sb;
    while ((page = page->next)->buf)
    {
        if (!page->changed)
            continue;

        if (page->nref > 0)
        {
            sbs = page->sbs;
            buf = page->buf;
            p_offset = 0;
            do
            {
                if (sb = *(struct sbuf **)(sbs + p_offset))
                    *(off_t *)(buf + p_offset) = db_sbuf_flush(sbio->db, *(off_t *)(buf + p_offset), sb);
            } while ((p_offset += sizeof(size_t)) < page_size);
        };
        page_next = page->next;
        idx_page_close(idx, page);
        page = page_next;
    };
    idx->anchor_page.next = idx->anchor_page.prev = &idx->anchor_page;
};

/* Public functions */

struct sbufio *sbufio_open(const char *const restrict filename)
{
    // Init handler
    struct sbufio *const restrict sbio = malloc(sizeof(struct sbufio));

    size_t f_len = strlen(filename);
    char *idx_f = alloca(f_len + sizeof(IDX_SUFFIX) + 1);
    memcpy(idx_f, filename, f_len);
    memcpy(idx_f + f_len, IDX_SUFFIX, sizeof(IDX_SUFFIX));
    idx_f[f_len + sizeof(IDX_SUFFIX)] = '\0';

    sbio->idx = idx_open(idx_f);
    sbio->db = db_open(filename);
    return sbio;
};

void sbufio_close(struct sbufio *const restrict sbio)
{
    sbufio_flush(sbio);
    idx_close(sbio->idx);
    db_close(sbio->db);
    free(sbio);
};

off_t sbufio_set(struct sbufio *const restrict sbio, off_t id, struct sbuf *restrict sb)
{
    struct sbufio_idx_page *idx_page;
    off_t p_offset;

    if (sb)
    {
        p_offset = idx_locate_sb(sbio->idx, sb, &idx_page);
        if (idx_page)
            idx_free(sbio->idx, p_offset, idx_page);
    }
    else
    {
        if (id < 0)
            return -1;
        sb = FREED_SBUF;
    };

    if (id < 0)
        id = idx_buf_available(sbio->idx);

    p_offset = idx_locate_id(sbio->idx, id, &idx_page);
    idx_free(sbio->idx, p_offset, idx_page);
    idx_set(sbio->idx, p_offset, idx_page, sb);

    return id;
};

struct sbuf *sbufio_get(struct sbufio *const restrict sbio, const off_t id)
{
    struct sbuf *sb;

    struct sbufio_idx_page *page;
    off_t p_offset = idx_locate_id(sbio->idx, id, page);

    struct sbuf *sb = *(struct sbuf **)(page->sbs + p_offset);
    if (sb && sb != FREED_SBUF)
        return sb;

    sb = NULL;
    off_t id_db = *(off_t *)(page->buf + p_offset);
    if (id_db > 0)
    {
        idx_set(sbio->idx, p_offset, page, sb = db_sbuf_get(sbio->db, id_db));
        ++page->nref;
    };

    return sb;
};

/**************************************
 * segbuf
 */

/*
 * Used as the default ->buf value, so that people can always assume
 * buf is non NULL and ->buf is NUL terminated even for a freshly
 * initialized strbuf.
 */
static struct sbuf *sbuf_init()
{
    struct sbuf *sb = malloc(sizeof(struct sbuf));
    sb->h.size = sb->h.used = 0;
    sb->buf = NULL;
    return sb;
};

struct sbuf *sbuf_alloc(const size_t size)
{
    struct sbuf *sb = sbuf_init();
    sb->h.used = 0;
    sb->h.size = size;
    sb->buf = size ? malloc(size) : NULL;
    return sb;
};

void sbuf_free(struct sbuf *const restrict sb)
{
    if (!sb || sb == FREED_SBUF)
        return;
    if (sb->buf)
        free(sb->buf);
    free(sb);
};

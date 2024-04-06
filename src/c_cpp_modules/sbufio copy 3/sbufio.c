#include <malloc.h>   // memalign
#include <stdlib.h>   // free
#include <sys/uio.h>  // iovec, preadv
#include <fcntl.h>    // open, F_WRLCK, F_UNLCK, F_SETLK
#include <sys/stat.h> // S_IRUSR, S_IWUSR
#include <unistd.h>   // close
#include <string.h>   // memcpy
#include "sbufio/sbufio.h"

/**************************************
 * utilities
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
 * sbufio_idx
 */

/* idx_page_* */

static struct sbufio_idx_page *idx_page_open(struct sbufio_idx *const restrict idx, const off_t offset)
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

static void idx_page_save(struct sbufio_idx *const restrict idx, struct sbufio_idx_page *page)
{
    write_page(
        idx->fd,
        page->offset,
        page->buf,
        idx->_page_size);
};

static void idx_page_close(struct sbufio_idx *const restrict idx, struct sbufio_idx_page *page)
{
    // #TODO:
    free(page->buf);
    free(page->sbs);
    free(page);
};

/* idx_locate_to_* */

static off_t idx_locate_to_id(struct sbufio_idx *const restrict idx, const off_t id, struct sbufio_idx_page **found_page)
{
    const off_t offset = id * sizeof(off_t),
                p_offset = offset % idx->_page_size,
                page_offset = offset - p_offset;

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

static off_t idx_locate_to_sb(struct sbufio_idx *const restrict idx, struct sbuf *sb, struct sbufio_idx_page **found_page)
{
    const size_t ps = idx->_page_size;
    struct sbufio_idx_page *restrict page = idx->anchor_page.next;
    off_t p_offset;

    if ((p_offset = (void *)sb - page->sbs) < 0 || p_offset >= ps) // if not first page
    {
        while ((p_offset = (void *)sb - (page = page->next)->sbs) < 0 || p_offset >= ps)
            if (page->offset < 0)
                return -1;

        (page->prev->next = page->next)->prev = page->prev;
        (((page->next = idx->anchor_page.next)->prev = page)->prev = &idx->anchor_page)->next = page; // move page to the first position
    };

    *found_page = page;
    return p_offset;
};

/* idx_id_* */
static void idx_id__set(struct sbufio_idx *const restrict idx, const off_t id, off_t value)
{
    struct sbufio_idx_page *idx_page;
    off_t p_offset = idx_locate_to_id(idx, id, &idx_page);
};

static void idx_id__get(struct sbufio_idx *const restrict idx, const off_t id, off_t value)
{
    struct sbufio_idx_page *idx_page;
    off_t p_offset = idx_locate_to_id(idx, id, &idx_page);
};

// available
static void idx_id_set(struct sbufio_idx *const restrict idx, const off_t id, off_t value){};
static void idx_id_free(struct sbufio_idx *const restrict idx, const off_t id)
{
    if (id < 1)
        return;

    struct sbufio_idx_page *id_page;
    off_t *id_p = idx_locate_to_id(idx, id, &id_page) + id_page->buf;
    off_t id_value = *id_p;

    if (id_value <= 0)
        return;

    struct sbufio_idx_page *i0_page;
    off_t *id0_p = idx_locate_to_id(idx, 0, &i0_page) + i0_page->buf;
    off_t N = *id0_p; // id0_value
    if (N - 1 == id)
    {
        *id_p = N_value;
        *id0_p = id; // N-1
        page->synced = false;
    };

    struct sbufio_idx_page *iN_page;
    off_t *N_p = idx_locate_to_id(idx, N, &iN_page) + iN_page->buf;
    off_t N_value = *N_p;
    page->synced = false;

    *id_p = N_value;
    *N_p = -id;

    // neu id nam ngay truoc N thi giam N xuong
};
static void idx_id_last(struct sbufio_idx *const restrict idx){};

/* idx_* */

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

    return idx;
};

static void idx_close(struct sbufio_idx *const restrict idx)
{
    // #TODO: force save, free all remain segbuf
    // #TODO: close pages
    idx->flock.l_type = F_UNLCK;
    fcntl(idx->fd, F_SETLKW, &idx->flock);
    close(idx->fd);
    free(idx);
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

    page->nref = 0;
    return page;
};

static void db_page_save(struct sbufio_db *const restrict db, struct sbufio_db_page *const restrict page)
{
    write_page(
        db->fd,
        page->offset,
        page->buf,
        db->_page_size);
};

static void db_page_close(struct sbufio_db *const restrict db, struct sbufio_db_page *const restrict page)
{
    // #TODO:
    free(page->buf);
    free(page);
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

    return db;
};

static void db_close(struct sbufio_db *const restrict db)
{
    // #TODO: close pages
    db->flock.l_type = F_UNLCK;
    fcntl(db->fd, F_SETLKW, &db->flock);
    close(db->fd);
    free(db);
};

static off_t db_alloc(struct sbufio_db *const restrict db, const off_t size)
{
    off_t offset = 0;
    // #TODO:
    return offset;
};

static off_t db_locate_to(struct sbufio_db *const restrict db, const off_t offset, struct sbufio_db_page **found_page)
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

static void db_read(struct sbufio_db *const restrict db, off_t offset, void *restrict buf, size_t nbyte)
{
    const off_t page_size = db->_page_size;
    struct sbufio_db_page *page;
    off_t p_offset;
    size_t load;
    while (nbyte)
    {
        p_offset = db_locate_to(db, offset, &page);
        if ((load = page_size - p_offset) > nbyte)
            load = nbyte;
        memcpy(buf, page->buf + p_offset, load);
        offset += load;
        buf += load;
        nbyte -= load;
    };
};

static void db_write(struct sbufio_db *const restrict db, off_t offset, void *restrict buf, size_t nbyte)
{
    const off_t page_size = db->_page_size;
    struct sbufio_db_page *page;
    off_t p_offset;
    size_t load;
    while (nbyte)
    {
        p_offset = db_locate_to(db, offset, &page);
        if ((load = page_size - p_offset) > nbyte)
            load = nbyte;
        page->changed = true;
        memcpy(page->buf + p_offset, buf, load);
        offset += load;
        buf += load;
        nbyte -= load;
    };
};

struct sbuf *db_sbuf_at(struct sbufio_db *const restrict db, const off_t offset)
{
    struct sbufio_db_page *db_page;
    off_t p_offset = db_locate_to(db, offset, &db_page);

    struct sbuf *sb = sbuf_init();
    sb->h = p_offset + db_page->buf;

    if (sb->h->used < db->_page_size - p_offset)
    {
        sb->buf = sb->h + sizeof(sb->h);
        sb->ref = db_page;
        ++db_page->nref;
        db_page->changed = true;
        return sb;
    };

    db_read(db, offset + sizeof(sb->h), sb->buf = malloc(sb->h->size), sb->h->size - sizeof(sb->h));

    return sb;
};

/**************************************
 * sbufio
 */

struct sbufio *sbufio_open(const char *const restrict filename)
{
    // Init handler
    struct sbufio *const restrict sbio = malloc(sizeof(struct sbufio));
    sbio->db = db_open(filename);
    sbio->idx = idx_open(filename); // #TODO: add suffix
    return sbio;
};

void sbufio_close(struct sbufio *const restrict sbio)
{
    idx_close(sbio->idx);
    db_close(sbio->db);
    free(sbio);
};

static struct sbuf SBUFIO_FREED;

struct sbuf *sbufio_get(struct sbufio *const restrict sbio, const off_t id)
{
    struct sbufio_idx_page *idx_page;
    off_t p_offset = idx_locate_to_id(sbio->idx, id, &idx_page);

    struct sbuf **sbuf_p = idx_page->sbs + p_offset;
    if (!*sbuf_p)
    {
        ++idx_page->nref;
        idx_page->changed = true;
        *sbuf_p = db_sbuf_at(sbio->db, *(void **)(idx_page->buf + p_offset));
    };
    return *sbuf_p;
};

off_t sbufio_set(struct sbufio *const restrict sbio, off_t id, struct sbuf *restrict sbuf)
{
    if (id < 0)
        id = 1000; // #TODO: get lowest available id

    struct sbufio_idx_page *idx_page;
    struct sbuf **id_p = idx_locate_to_id(sbio->idx, id, &idx_page) + idx_page->sbs;
    struct sbuf *id_value = *id_p;

    if (id_value && id_value != &SBUFIO_FREED)
    {
        --idx_page->nref;
        idx_page->changed = true;
        sbufio_free(id_value);
    };

    if (sbuf)
    {
        ++idx_page->nref;
    }
    else
    {
        sbuf = &SBUFIO_FREED;
    }

    *id_p = sbuf;

    return id;
};

void sbufio_free_all(struct sbuf *sb){};

off_t sbufio_find_id(struct sbufio *const restrict sbio, struct sbuf *const restrict sb)
{
    // #TODO:
    return -1; // not found
};

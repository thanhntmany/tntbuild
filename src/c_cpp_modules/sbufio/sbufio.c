#include <stdlib.h> // malloc
#include <string.h> // memcmp, memcpy
#include "sbufio/sbufio.h"

/**************************************
 * sdb: segments management
 */

static sbufio_sdb_offset sdb_alloc(struct sbufio_sdb *const restrict sdb, struct sbuf *const restrict sb)
{
    const off_t offset = sdb->tail;
    sdb->tail += sizeof(sb->h) + sb->h.alloc;

    iofp_write(sdb->fp, offset, &sb->h, sizeof(sb->h));
    iofp_write(sdb->fp, offset + sizeof(sb->h), sb->buf, sb->h.size);
    return offset;
};

static struct sbuf *sdb_get(struct sbufio_sdb *sdb, const off_t offset)
{
    struct sbuf_header h;
    iofp_read(sdb->fp, offset, &h, sizeof(h));

    if (h.alloc > 0)
    {
        struct sbuf *sb = sbuf_init();
        sb->h = h;
        iofp_read(sdb->fp, offset + sizeof(sb->h), sb->buf = malloc(sb->h.alloc), sb->h.size);
        return sb;
    };

    return NULL;
};

static sbufio_sdb_offset sdb_set(struct sbufio_sdb *const restrict sdb, const off_t offset, struct sbuf *const restrict sb)
{
    struct sbuf_header h;
    iofp_read(sdb->fp, offset, &h, sizeof(h));
    if (h.alloc < sb->h.size)
        return 0;

    h.size = sb->h.size;
    iofp_write(sdb->fp, offset, &h, sizeof(h));
    iofp_write(sdb->fp, offset + sizeof(h), sb->buf, sb->h.size);
    return offset;
};

static void sdb_free(struct sbufio_sdb *sdb, sbufio_sdb_offset offset)
{
    struct sbuf_header h;
    iofp_read(sdb->fp, offset, &h, sizeof(h));
    h.size = 0;
    iofp_write(sdb->fp, offset, &h, sizeof(h));
    sdb->sumoffree += h.alloc;
};

static sbufio_sdb_offset sdb_update(struct sbufio_sdb *sdb, sbufio_sdb_offset offset, struct sbuf *sb)
{
    sbufio_sdb_offset out_offset = sdb_set(sdb, offset, sb);
    if (out_offset)
        return out_offset;

    sdb_free(sdb, offset);
    return sdb_alloc(sdb, sb);
};

/**************************************
 * idx: indexing management
 */

static void idx_free(struct sbufio *const restrict sbio, sbufio_idx_id id)
{
    struct iofp_page *page;
    sbufio_sdb_offset *id_p = iofp_locate(sbio->idx.fp, id * sizeof(sbufio_sdb_offset), &page),
                      sdb_offset = *id_p;
    if (sdb_offset)
    {
        sdb_free(&sbio->sdb, sdb_offset);
        *id_p = 0;
        page->changed = true;
    };

    if (id < sbio->idx.la)
        sbio->idx.la = id;
};

static void idx_update(struct sbufio *const restrict sbio, const sbufio_idx_id id, struct sbuf *sb)
{
    struct iofp_page *page;
    sbufio_sdb_offset *id_p = iofp_locate(sbio->idx.fp, id * sizeof(sbufio_sdb_offset), &page),
                      sdb_offset = *id_p;
    *id_p = sdb_offset ? sdb_update(&sbio->sdb, sdb_offset, sb) : sdb_alloc(&sbio->sdb, sb);
    if (*id_p != id)
        page->changed = true;
};

/**************************************
 * Main functions
 */

static char _SFILE_SIGNATURE[] = SFILE_SIGNATURE;

static struct sbuf _IDM_EMPTY;
static struct sbuf *IDM_EMPTY = &_IDM_EMPTY;

static char IDX_SUFFIX[] = ".idx";

struct sbufio *sbufio_open(const char *const restrict filename)
{
    // Init handler
    struct sbufio *const restrict sbio = malloc(sizeof(struct sbufio));
    size_t f_len = strlen(filename);
    char *idx_f = alloca(f_len + sizeof(IDX_SUFFIX) + 1);
    memcpy(idx_f, filename, f_len);
    memcpy(idx_f + f_len, IDX_SUFFIX, sizeof(IDX_SUFFIX));
    idx_f[f_len + sizeof(IDX_SUFFIX)] = '\0';

    sbio->idm = memp_open();
    sbio->idx.fp = iofp_open(idx_f);
    sbio->sdb.fp = iofp_open(filename);

    struct sbufio_metadata *meta = &sbio->meta;
    iofp_read(sbio->sdb.fp, 0, meta, sizeof(*meta));

    if (memcmp(&meta->signature, _SFILE_SIGNATURE, sizeof(SFILE_SIGNATURE)))
    {
        memcpy(&meta->signature, _SFILE_SIGNATURE, sizeof(SFILE_SIGNATURE));
        meta->sdb_tail = sizeof(meta);
        meta->sdb_sumoffree = 0;
        meta->idx_la = 0;
    };

    sbio->idx.la = meta->idx_la;
    sbio->sdb.tail = meta->sdb_tail;
    sbio->sdb.sumoffree = meta->sdb_sumoffree;

    return sbio;
};

void sbufio_flush(struct sbufio *const restrict sbio)
{
    struct memp *idm = sbio->idm;
    size_t page_size = idm->page_size;
    struct memp_page *page = idm->anchor.next, *page_next;
    int nref;
    off_t page_offset, p_offset;
    sbufio_idx_id id;
    void *buff;
    struct sbuf *sb, **sb_p;

    while ((buff = page->buff))
    {
        page_offset = page->offset;
        p_offset = 0;
        nref = page->nref;
        while (nref > 0 && p_offset < page_size)
        {
            if ((sb = *(sb_p = buff + p_offset)))
            {
                id = (page_offset + p_offset) / sizeof(sbufio_idm_value);
                if (sb == IDM_EMPTY)
                {
                    idx_free(sbio, id);
                }
                else
                {
                    idx_update(sbio, id, sb);
                    sb->independence = true;
                    sbuf_free(sb);
                };
                *sb_p = NULL;
                --nref;
            };
            p_offset += sizeof(struct sbuf **);
        };
        page_next = page->next;
        memp_store_page(idm, page);
        page = page_next;
    };

    // Store metadata
    struct sbufio_metadata *meta = &sbio->meta;
    meta->idx_la = sbio->idx.la;
    meta->sdb_tail = sbio->sdb.tail;
    meta->sdb_sumoffree = sbio->sdb.sumoffree;
    iofp_write(sbio->sdb.fp, 0, meta, sizeof(*meta));

    iofp_flush(sbio->idx.fp);
    iofp_flush(sbio->sdb.fp);
};

void sbufio_close(struct sbufio *const restrict sbio)
{
    sbufio_flush(sbio);
    memp_close(sbio->idm);
    iofp_close(sbio->idx.fp);
    iofp_close(sbio->sdb.fp);
    free(sbio);
};

/* operations */

static sbufio_idx_id sbufio_available_id(struct sbufio *const restrict sbio)
{
    struct memp *idm = sbio->idm;
    struct memp_page *idm_page;
    struct sbuf *sb;
    struct iofp *idx_fp = sbio->idx.fp;
    struct iofp_page *idx_page;

    sbufio_idx_id id = sbio->idx.la;
loop:
    if ((sb = *(struct sbuf **)memp_locate(idm, id * sizeof(sbufio_idm_value), &idm_page)))
    {
        if ((sb == IDM_EMPTY))
            goto ret;
    }
    else if (!*(sbufio_sdb_offset *)iofp_locate(idx_fp, id * sizeof(sbufio_sdb_offset), &idx_page))
        goto ret;
    ++id;
    goto loop;
ret:
    return sbio->idx.la = id;
};

sbufio_idx_id sbufio_set(struct sbufio *const restrict sbio, sbufio_idx_id id, struct sbuf *restrict new_sb)
{

    if (id <= 0)
        id = sbufio_available_id(sbio);

    struct memp_page *page;
    struct sbuf **sb_p = memp_locate(sbio->idm, id * sizeof(sbufio_idm_value), &page);

    if (!*sb_p)
        ++page->nref;

    if (new_sb)
    {
        if (!new_sb->independence)
            new_sb = sbuf_dup(new_sb);
        *sb_p = new_sb;
        new_sb->independence = false;
        if (id == sbio->idx.la)
            sbio->idx.la = id + 1;
    }
    else
    {
        *sb_p = IDM_EMPTY;
        if (id < sbio->idx.la)
            sbio->idx.la = id;
    };

    return id;
};

struct sbuf *sbufio_get(struct sbufio *const restrict sbio, const sbufio_idx_id id)
{
    if (id < 0)
        return NULL;
    struct memp_page *idm_page;
    struct sbuf **sb_p = memp_locate(sbio->idm, id * sizeof(sbufio_idm_value), &idm_page);
    struct sbuf *sb = *sb_p;

    if (!sb)
    {
        struct iofp_page *idx_page;
        sbufio_sdb_offset sdb_offset = *(sbufio_sdb_offset *)iofp_locate(sbio->idx.fp, id * sizeof(sbufio_sdb_offset), &idx_page);
        if (sdb_offset)
        {
            sb = sdb_get(&sbio->sdb, sdb_offset);
            sb->independence = false;
        };

        *sb_p = sb = sb ? sb : IDM_EMPTY;
        ++idm_page->nref;
    };

    return sb == IDM_EMPTY ? NULL : sb;
};

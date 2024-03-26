#include <stdio.h>
#include <stdlib.h> //malloc, alloca
#include <string.h> // memcpy, strcat
#include "sfile/sfile.h"

sfile_offset idb_get(const struct sfile *const restrict sf, const sfile_id id)
{
    sfile_offset offset;
    pstream_read(sf->pstreams.idb, id * sizeof(sfile_offset), &offset, sizeof(sfile_offset));
    return offset;
};

static void idb_set(const struct sfile *const restrict sf, const sfile_id id, const sfile_offset offset)
{
    pstream_write(sf->pstreams.idb, id * sizeof(sfile_offset), &offset, sizeof(sfile_offset));
};

static void db_read_segheader(const struct sfile *restrict sf, const sfile_offset offset, struct sfile_fdb_segheader *const restrict sgh)
{
    pstream_read(sf->pstreams.db, offset, sgh, sizeof(struct sfile_fdb_segheader));
};

static void db_write_segheader(struct sfile *const restrict sf, const sfile_offset offset, const struct sfile_fdb_segheader *restrict sgh)
{
    pstream_write(sf->pstreams.db, offset, sgh, sizeof(struct sfile_fdb_segheader));
};

static void db_read_seg(const struct sfile *restrict sf, const sfile_offset offset, void *const restrict buffer, const size_t buffer_size)
{
    pstream_read(sf->pstreams.db, offset + sizeof(struct sfile_fdb_segheader), buffer, buffer_size);
};

static void db_write_seg(const struct sfile *restrict sf, const sfile_offset offset, const void *const restrict buffer, const size_t buffer_size)
{
    pstream_write(sf->pstreams.db, offset + sizeof(struct sfile_fdb_segheader), buffer, buffer_size);
};

static sfile_offset db_alloc(struct sfile *const restrict sf, const void *const restrict buffer, const size_t buffer_size)
{
    size_t offset = sf->header.next_offset;

    const struct sfile_fdb_segheader sgh = {.used = buffer_size, .size = buffer_size};
    db_write_segheader(sf, offset, &sgh);
    db_write_seg(sf, offset, buffer, buffer_size);

    sf->header.next_offset += sizeof(struct sfile_fdb_segheader) + buffer_size;
    return offset;
};

static sfile_offset db_free(struct sfile *const restrict sf, const sfile_offset offset)
{
    struct sfile_fdb_segheader sgh;
    db_read_segheader(sf, offset, &sgh);
    sgh.used = 0;
    db_write_segheader(sf, offset, &sgh);
};

/* MAIN **************************************/

struct sfile *sfile_open(const char *restrict db_path, const size_t db_poolsize, const size_t idb_poolsize)
{
    struct sfile *restrict sf = malloc(sizeof(struct pstream));
    sf->pstreams.db = pstream_open(db_path, db_poolsize);

    size_t db_path_len = strlen(db_path);
    char *restrict idx_path = alloca(db_path_len + 5);
    memcpy(idx_path, db_path, db_path_len);
    memcpy(idx_path + db_path_len, IDX_SUFFIX, sizeof(IDX_SUFFIX));
    sf->pstreams.idb = pstream_open(idx_path, idb_poolsize);

    pstream_lock(sf->pstreams.db);
    pstream_lock(sf->pstreams.idb);

    /* Read header data */
    pstream_read(sf->pstreams.db, 0, &sf->header, sizeof(sf->header));
    // validate signature
    if (memcmp(sf->header.sfile_signature, SFILE_SIGNATURE, sizeof(SFILE_SIGNATURE)))
    {
        memcpy(sf->header.sfile_signature, SFILE_SIGNATURE, sizeof(SFILE_SIGNATURE));
        sf->header.next_offset = sizeof(sf->header);
        sf->header.next_id = 0;
        sf->header.last_free = 0;
        pstream_write(sf->pstreams.db, 0, &sf->header, sizeof(sf->header));
    };

    return sf;
};

void sfile_flush(struct sfile *const restrict sf)
{
    pstream_write(sf->pstreams.db, 0, &sf->header, sizeof(sf->header));
    pstream_flush(sf->pstreams.db);
    pstream_flush(sf->pstreams.idb);
};

void sfile_close(struct sfile *const restrict sf)
{
    sfile_flush(sf);
    pstream_unlock(sf->pstreams.db);
    pstream_unlock(sf->pstreams.idb);
    pstream_close(sf->pstreams.db);
    pstream_close(sf->pstreams.idb);

    free(sf);
};

sfile_id sfile_alloc(struct sfile *const restrict sf, const char *restrict buffer, const size_t size)
{
    idb_set(sf, sf->header.next_id, db_alloc(sf, buffer, size));
    return sf->header.next_id++;
};

size_t sfile_read_size(struct sfile *const restrict sf, const sfile_id id)
{
    sfile_offset offset = idb_get(sf, id);
    if (!offset)
        return 0;

    struct sfile_fdb_segheader sgh;
    db_read_segheader(sf, offset, &sgh);
    return sgh.used;
};

size_t sfile_read(struct sfile *const restrict sf, const sfile_id id, void *const restrict buffer, const size_t buffer_size)
{
    sfile_offset offset = idb_get(sf, id);
    if (!offset)
        return 0; // null data

    struct sfile_fdb_segheader sgh;
    db_read_segheader(sf, offset, &sgh);
    if (buffer_size < sgh.used)
        return -1; // error

    db_read_seg(sf, offset, buffer, sgh.used);
    return sgh.used; // The return value is the number of bytes actually read.
};

void sfile_write(struct sfile *const restrict sf, const sfile_id id, void *restrict buffer, const size_t buffer_size)
{
    sfile_offset offset = idb_get(sf, id);
    if (offset)
    {
        struct sfile_fdb_segheader sgh;
        db_read_segheader(sf, offset, &sgh);
        if (buffer_size <= sgh.size)
        {
            if (buffer_size != sgh.used)
            {
                sgh.used = buffer_size;
                db_write_segheader(sf, offset, &sgh);
            };
            db_write_seg(sf, offset, buffer, buffer_size);
            return;
        }
        else
            db_free(sf, offset);
    };

    idb_set(sf, id, db_alloc(sf, buffer, buffer_size));
};

void *sfile_free(struct sfile *const restrict sf, const sfile_id id)
{
    db_free(sf, idb_get(sf, id));
    idb_set(sf, id, 0);
};

void *sfile_defrag(struct sfile *sf){
    // @TODO:
};

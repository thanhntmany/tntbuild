#include <stdio.h>
#include <stdlib.h> //malloc, alloca
#include <string.h> // memcpy, strcat
#include "sfile/sfile.h"

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

void sfile_flush(struct sfile *sf)
{
    pstream_write(sf->pstreams.db, 0, &sf->header, sizeof(sf->header));
    pstream_flush(sf->pstreams.db);
    pstream_flush(sf->pstreams.idb);
};

void sfile_close(struct sfile *sf)
{
    sfile_flush(sf);
    pstream_unlock(sf->pstreams.db);
    pstream_unlock(sf->pstreams.idb);
    pstream_close(sf->pstreams.db);
    pstream_close(sf->pstreams.idb);

    free(sf);
};

sfile_id sfile_alloc(struct sfile *restrict sf, const char *restrict buff, const size_t size)
{
    sfile_id id = sf->header.next_id;
    pstream_write(
        sf->pstreams.idb, id * sizeof(sf->header.next_offset),
        &sf->header.next_offset, sizeof(sf->header.next_offset));

    const struct sfile_fdb_segheader seg_header = {.used = size, .size = size};
    size_t p = sf->header.next_offset;
    pstream_write(sf->pstreams.db, p, &seg_header, sizeof(struct sfile_fdb_segheader));
    pstream_write(sf->pstreams.db, p += sizeof(struct sfile_fdb_segheader), buff, size);

    sf->header.next_offset = p + size;
    ++sf->header.next_id;

    return id;
};

void *sfile_get(struct sfile *sf, sfile_id id){};

void *sfile_set(struct sfile *sf, sfile_id id, char *buff, size_t size){};

void *sfile_free(struct sfile *sf, sfile_id id, char *buff, size_t size){};

void *sfile_defrag(struct sfile *sf){};

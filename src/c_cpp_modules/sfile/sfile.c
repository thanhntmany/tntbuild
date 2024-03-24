#include <stdio.h>
#include <stdlib.h> //malloc
#include <string.h> // memcpy, strcat
#include "sfile/sfile.h"

struct sfile *sfile_open(const char *restrict db_path, const size_t db_poolsize, const size_t idb_poolsize)
{
    struct sfile *restrict sf = malloc(sizeof(struct pstream));
    sf->pstreams.db = pstream_open(db_path, db_poolsize);

    size_t db_path_len = strlen(db_path);
    char *restrict idx_path = malloc(db_path_len + 5);
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
        sf->header.next_idx = 0;
        sf->header.last_free = 0;
        pstream_write(sf->pstreams.db, 0, &sf->header, sizeof(sf->header));
    };

    return sf;
};

void sfile_close(struct sfile *sf)
{
    pstream_flush(sf->pstreams.db);
    pstream_flush(sf->pstreams.idb);
    pstream_unlock(sf->pstreams.db);
    pstream_unlock(sf->pstreams.idb);
    pstream_close(sf->pstreams.db);
    pstream_close(sf->pstreams.idb);

    free(sf);
};

sfile_fidb_id sfile_alloc(struct sfile *sf, char *buff, size_t size){

};

void *sfile_get(struct sfile *sf, sfile_fidb_id id){};

void *sfile_set(struct sfile *sf, sfile_fidb_id id, char *buff, size_t size){};

void *sfile_free(struct sfile *sf, sfile_fidb_id id, char *buff, size_t size){};

void *sfile_defrag(struct sfile *sf){};

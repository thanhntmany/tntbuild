#ifndef SFILE_H
#define SFILE_H

#include "pstream/pstream.h" //pstream

/*
 * Prefer x64 architecture
 */

#define SFILE_SIGNATURE "tnt/sfile:0.0.1"
#define IDX_SUFFIX ".idx"

typedef size_t sfile_id;
typedef size_t sfile_offset;

struct __attribute__((packed)) sfile_fdb_header
{
    char sfile_signature[sizeof(SFILE_SIGNATURE)];
    sfile_offset next_offset;
    sfile_id next_id;
    size_t last_free; // --> backward linked list
};

struct __attribute__((packed)) sfile_fdb_segheader
{
    size_t used;
    size_t size;
};

struct sfile
{
    struct pstreams
    {
        struct pstream *db;
        struct pstream *idb;
    } pstreams;
    struct sfile_fdb_header header;
};

struct sfile *sfile_open(const char *restrict db_path, const size_t db_poolsize, const size_t idb_poolsize);

void sfile_flush(struct sfile *const restrict sf);

void sfile_close(struct sfile *const restrict sf);

sfile_id sfile_alloc(struct sfile *const restrict sf, const char *restrict buffer, const size_t size);

size_t sfile_get(struct sfile *const restrict sf, const sfile_id id, void *const restrict buffer, const size_t buffer_size);

void sfile_set(struct sfile *const restrict sf, const sfile_id id, void *restrict buffer, const size_t buffer_size);

#endif

#ifndef SFILE_H
#define SFILE_H

#include "pstream/pstream.h" //pstream

/*
 * Prefer x64 architecture
 */

#define SFILE_SIGNATURE "tnt/sfile:0.0.1"
#define IDX_SUFFIX ".idx"

typedef size_t sfile_id;

struct __attribute__((packed)) sfile_fdb_header
{
    char sfile_signature[sizeof(SFILE_SIGNATURE)];
    size_t next_offset;
    sfile_id next_id;
    size_t last_free; // --> backward linked list
};

struct __attribute__((packed)) sfile_fdb_segheader
{
    size_t used;
    size_t size;
    // size_t prev_free_seg; only while ".used==0"
};

struct sfile_fidb
{
    struct idx
    {
        size_t f_offset; // =0 mean Nothing
    } *idx;
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

void sfile_close(struct sfile *sf);

void sfile_flush(struct sfile *sf);

sfile_id sfile_alloc(struct sfile *restrict sf, const char *restrict buff, const size_t size);

#endif

#ifndef SFILE_H
#define SFILE_H

#include "pstream/pstream.h" //pstream

/*
 * Prefer x64 architecture
 */

struct sfile_fdb_header
{
    size_t next_seg_offset;
    size_t next_idx;
    size_t last_free_seg; // --> backward linked list
};

struct sfile_fdb_segheader
{
    size_t used;
    size_t size;
    // size_t prev_free_seg; only while ".used==0"
};

typedef size_t sfile_fidb_id;

struct sfile_fidb
{
    struct idx
    {
        size_t f_offset; // =0 mean Nothing
    } *idx;
};

struct sfile
{
    char *pathname;
    struct pstream *db_pstream;
    struct pstream *idb_pstream;
};

#endif

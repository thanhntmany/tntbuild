#include <stdio.h>
#include <string.h> // strcat
#include "sfile/sfile.h"

int sfile_open(struct sfile *sf, const char *filename)
{
    sf->db_pstream = malloc(sizeof(struct pstream));
    sf->idb_pstream = malloc(sizeof(struct pstream));
    pstream_open(&sf->db_pstream, filename)
};

void sfile_close(struct sfile *sf)
{
    pstream_close(sf->db_pstream);
    pstream_close(sf->idb_pstream);
};

sfile_fidb_id sfile_alloc(struct sfile *sf, char *buff, size_t size){};

void *sfile_get(struct sfile *sf, sfile_fidb_id id){};

void *sfile_set(struct sfile *sf, sfile_fidb_id id, char *buff, size_t size){};

void *sfile_free(struct sfile *sf, sfile_fidb_id id, char *buff, size_t size){};

void *sfile_defrag(struct sfile *sf){};

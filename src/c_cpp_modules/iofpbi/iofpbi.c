#include <stdlib.h>  // malloc
#include <stdbool.h> // bool
#include <string.h>  // memcmp, memcpy
#include "iofpbi/iofpbi.h"

struct iofpbi *iofpbi_open(const char *const restrict filename)
{
    struct iofpbi *const restrict fpbi = malloc(sizeof(struct iofpbi));
    fpbi->fpb = iofpb_open(filename);
    fpbi->fpi = iofpi_open(filename);
    return fpbi;
};

void iofpbi_close(struct iofpbi *const restrict fpbi)
{
    iofpb_close(fpbi->fpb);
    iofpi_close(fpbi->fpi);
    free(fpbi);
};

void iofpbi_alloc(struct iofpbi *const restrict fpbi, size_t size, struct iofpb_blockh *const restrict bh);
void iofpbi_assignid(struct iofpbi *const restrict fpbi, iofpi_id id, struct iofpb_blockh *const restrict bh);
void iofpbi_getbyid(struct iofpbi *const restrict fpbi, iofpi_id id, struct iofpb_blockh *const restrict bh);
void iofpbi_freebyid(struct iofpbi *const restrict fpbi, iofpi_id id);
void iofpbi_defrag(struct iofpbi *const restrict fpbi);

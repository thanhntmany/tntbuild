#include <stdlib.h>  // malloc
#include <stdbool.h> // bool
#include <string.h>  // memcmp, memcpy
#include "iofpi/iofpi.h"

struct iofpi *iofpi_open(const char *const restrict filename)
{
    struct iofpi *const restrict fpi = malloc(sizeof(struct iofpi));
    fpi->fp = iofp_open(filename);
    return fpi;
};

void iofpi_set(struct iofpi *const restrict fpi, const iofpi_id id, const iofpi_value value)
{
    struct iofp_page *page;
    *(iofpi_value *)iofp_ptrtooffset(fpi->fp, id * sizeof(iofpi_id), &page) = value;
    iofp_markpagechanged(page);
};

iofpi_value iofpi_get(struct iofpi *const restrict fpi, const iofpi_id id)
{
    struct iofp_page *page;
    return *(iofpi_value *)iofp_ptrtooffset(fpi->fp, id * sizeof(iofpi_id), &page);
};

void iofpi_close(struct iofpi *const restrict fpi)
{
    iofp_close(fpi->fp);
    free(fpi);
};

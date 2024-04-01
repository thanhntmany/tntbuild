#ifndef IOFPI_H
#define IOFPI_H

#include <stdint.h>
#include "iofp/iofp.h"

typedef off_t iofpi_id;
typedef off_t iofpi_value;

struct iofpi
{
    struct iofp *fp;
};

struct iofpi *iofpi_open(const char *const filename);

void iofpi_set(struct iofpi *const fpi, const iofpi_id id, const iofpi_value value);

iofpi_value iofpi_get(struct iofpi *const fpi, const iofpi_id id);

void iofpi_close(struct iofpi *const fpi);

#endif

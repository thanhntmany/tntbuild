#include <stdio.h>
#include <string.h>
#include "iofpi/iofpi.h"

int main()
{
    printf("Load ok\n");

    struct iofpi *fpi = iofpi_open("dbi.idx");

    iofpi_set(fpi, 10, 0xff);
    iofpi_set(fpi, 11, 'T');
    iofpi_set(fpi, 12, 'H');

    printf("iofpi_get: %ld", iofpi_get(fpi, 12));

    iofpi_close(fpi);

    return 0;
};

#ifndef IOFPBI_H
#define IOFPBI_H

#include <stdint.h>
#include "iofp/iofp.h"
#include "iofpb/iofpb.h"
#include "iofpi/iofpi.h"

struct iofpbi
{
    struct iofpb *fpb;
    struct iofpi *fpi;
};

#endif

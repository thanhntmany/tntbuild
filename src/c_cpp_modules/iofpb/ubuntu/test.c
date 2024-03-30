#include <stdio.h>
#include <string.h>
#include "iofpb/iofpb.h"

int main()
{
    printf("Load ok\n");

    struct iofpb *fpb = iofpb_open("test_fpb.db");

    printf("Loaded:\n");
    printf("-> next_offset: %ld\n", fpb->f->next_offset);

    struct iofpb_fblockh *block = iofpb_alloc(fpb, 4049);

    char *new = "QQQQQQQQQQQQQQQQQQQQ12345";
    memcpy(iofpb_buffofblock(block), new, strlen(new));

    printf("-> next_offset: %ld\n", fpb->f->next_offset);

    iofpb_close(fpb);

    return 0;
};

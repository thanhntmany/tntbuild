#include <stdio.h>
#include <string.h>
#include "iofpb/iofpb.h"

int main()
{
    printf("Load ok\n");

    struct iofpb *fpb = iofpb_open("test_fpb.db");

    printf("Loaded:\n");
    printf("-> next_offset: %ld\n", fpb->f->next_offset);

    struct iofpb_blockh bh;

    char *new = "QQQQQQQQQQQQQQQQQQQQ12345";
    memcpy(iofpb_alloc(fpb, strlen(new), &bh), new, strlen(new));
    iofpb_free(&bh);


    new = "123456789XXXXXXXX987654321";
    memcpy(iofpb_alloc(fpb, strlen(new), &bh), new, strlen(new));


    printf("-> next_offset: %ld\n", fpb->f->next_offset);

    iofpb_close(fpb);

    return 0;
};

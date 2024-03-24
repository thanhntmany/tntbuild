#include <stdio.h>
#include "sfile/sfile.h"

int main()
{
    printf("Test\n");
    struct sfile *sf = sfile_open("_test_db.db", 256 * 1024, 4 * 1024);

    sfile_close(sf);
    return 0;
};

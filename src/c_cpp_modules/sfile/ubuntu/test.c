#include <stdio.h>
#include "sfile/sfile.h"

int main()
{
    printf("Test\n");
    struct sfile *sf = sfile_open("_test_db.db", 256 * 1024, 4 * 1024);

    char data[] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    sfile_id id = sfile_alloc(sf, data, sizeof(data));
    printf("new id: %ld\n", id);

    sfile_close(sf);
    return 0;
};

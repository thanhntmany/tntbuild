#include <stdio.h>
#include "sfile/sfile.h"

int main()
{
    printf("Test\n");
    struct sfile *sf = sfile_open("_test_db.db", 256 * 1024, 4 * 1024);

    char data[6114] = "Nguyễn Thuận Thành, Nguyễn Thuận Thành, Nguyễn Thuận Thành, Nguyễn Thuận Thành, Nguyễn Thuận Thành, Nguyễn Thuận Thành0123456789";
    sfile_id id = sfile_alloc(sf, data, sizeof(data));
    printf("new id: %ld\n", id);

    printf("sfile_read N.o bytes read: %ld\n", sfile_read(sf, id, data, sizeof(data)));
    // printf("sfile_read N.o bytes read: %ld\n", sfile_read(sf, id, data, 6114));
    printf("sfile_read: <%s>\n", data);

    sfile_flush(sf);
    sfile_close(sf);
    return 0;
};

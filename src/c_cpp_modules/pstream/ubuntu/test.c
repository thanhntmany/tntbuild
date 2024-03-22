#include <string.h> // strlen
#include "pstream/pstream.h"

int main()
{
    char *test = "0123456789012345678901234567890123456789";
    char buff[50];

    struct pstream *ps = pstream_open("./pstreamtest.db", 512);
    pstream_lockwrite(ps);

    pstream_read(ps, 4090, buff, 10);
    buff[10] = 0;
    printf("Read  : %s\n", buff);

    pstream_write(ps, 4090, test, strlen(test));
    printf("Write : Done\n");

    pstream_unlockwrite(ps);
    pstream_close(ps);

    return 0;
};

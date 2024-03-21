#include <stdio.h>
#include <stdlib.h> // free
#include "strbuf/strbuf.h"

int main()
{
    struct strbuf *sb = strbuf_init(256);
    strbuf_loadstr(sb, "test something here 123456789");

    char *test = strbuf_tostr(sb);
    printf("1.Show: \"%s\"\n", test);
    free(test);

    printf("2.Show: \"%s\"\n", strbuf_asstr(sb));

    strbuf_free(sb);
    return 0;
};

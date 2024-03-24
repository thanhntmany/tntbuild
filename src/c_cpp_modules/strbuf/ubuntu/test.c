#include <stdio.h>
#include <stdlib.h> // free
#include "strbuf/strbuf.h"

int main()
{
    struct strbuf *sb = strbuf_from("test something here 123456789", 23, 10);

    char *test = strbuf_tostr(sb);
    printf("1.Show: \"%s\"\n", test);
    free(test);


    strbuf_load(sb, 19, "test load text", 15);
    printf("2.Show: \"%s\"\n", strbuf_asstr(sb));

    strbuf_free(sb);
    return 0;
};

#include <stdio.h>
#include "sbufio/sbufio.h"

int main()
{
    printf("Load ok\n");

    struct sbuf *sb1 = sbuf_from_str("short");
    printf("sb1: %s\n", sbuf_as_str(sb1));

    struct sbufio *sbio = sbufio_open("./sbiodata.db");

    sbufio_id id = sbufio_set(sbio, -1, sb1);
    printf("Set as id: %ld\n", id);
    printf("sbufio_get(sbio, id): %p\n", sbufio_get(sbio, id));
    if (sbufio_get(sbio, id))
        printf("text: [%s]\n", sbuf_as_str(sbufio_get(sbio, id)));

    if (id > 2)
    {
        id = sbufio_set(sbio, id - 2, sb1);
        printf("Set as id: %ld\n", id);
        printf("sbufio_get(sbio, id): %p\n", sbufio_get(sbio, id));
        if (sbufio_get(sbio, id))
            printf("text: [%s]\n", sbuf_as_str(sbufio_get(sbio, id)));
    }

    printf("sbufio_close\n");
    sbufio_close(sbio);

    return 0;
};

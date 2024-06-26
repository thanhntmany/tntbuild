#include <stdio.h>
#include "iofp/iofp.h"

int main()
{
    printf("Load ok\n");

    printf("iofp_open\n");
    struct iofp *fp = iofp_open("./data.db");

    printf("iofp_locate\n");
    struct iofp_page *page;
    struct testst
    {
        size_t a;
        size_t b;
    } *obj = iofp_locate(fp, 4080, &page);

    printf("iofp_locate: %p\n", obj);

    obj->a = 'X';
    obj->b = 'Y';
    page->changed = true;

    printf("iofp_locate: %s\n", (char *)obj);

    printf("iofp_offsettoptr: %d\n", (int)iofp_offsettoptr(fp, obj, &page));
    // printf("iofp_toendofpage: %d\n", iofp_toendofpage(fp, 4080));

    printf("iofp_write\n");
    char buff[50] = "0123456789 asdads sadhfjsa XXXXX 0123456789";
    iofp_write(fp, 4090, buff, sizeof(buff));
    iofp_write(fp, 3*4090, buff, sizeof(buff));


    printf("iofp_read\n");
    iofp_read(fp, 4090, buff, sizeof(buff) - 3);
    printf("Buff: %s\n", buff);

    printf("iofp_close\n");
    // iofp_close(fp);

    return 0;
};

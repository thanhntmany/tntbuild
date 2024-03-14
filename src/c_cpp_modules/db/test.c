#include <stdio.h>

int main()
{
    struct test
    {
        size_t offset;
        size_t size;
    } varTest[65536];

    printf("----------\n");
    printf("Sizeof %ld\n", sizeof varTest);

    return 0;
};

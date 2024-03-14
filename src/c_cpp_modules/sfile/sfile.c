#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sfile.h"

static SFile_IPage *mallocIPage()
{
    SFile_IPage *ptr = (SFile_IPage *)malloc(sizeof(SFile_IPage));
    if (!ptr) // ptr == 0 // #TODO:
        abort();
    memset(ptr, 0, sizeof(SFile_IPage));
    return ptr;
};

void freeIPage(SFile_IPage *ptr)
{
    free(ptr);
};

void sfile_init(SFileHandler *sf, FILE *io)
{
    sf->io = io;
    sf->root = mallocIPage();
};

void sfile_release(SFileHandler *sf){
    // #TODO:
};

void sfile_get(SFileHandler *sf, SFile_Key *key, SFile_SegDec *segdec)
{
    printf("key->id --> %.8X : ", key->id);
    printf(" %d - %d - %d - %d\n", key->p[3], key->p[2], key->p[1], key->p[0]);
    printf("-----------------------------\n");

    void **o_ptr = &(sf->root->idx[key->p[3]]);
    if (!*o_ptr)
        *o_ptr = mallocIPage();

    o_ptr = &(((SFile_IPage *)*o_ptr)->idx[key->p[2]]);
    if (!*o_ptr)
        *o_ptr = mallocIPage();

    o_ptr = &(((SFile_IPage *)*o_ptr)->idx[key->p[1]]);
    if (!*o_ptr)
    {
        *o_ptr = (SFile_Page *)malloc(sizeof(SFile_Page));
        if (!*o_ptr) // #TODO:
            abort();
        memset(*o_ptr, 0, sizeof(SFile_Page));
        // #TODO: Load page segment in file
        // Should use stream with buffer = sizeof(SFile_Page)
    };

    *segdec = ((SFile_Page *)*o_ptr)->idx[key->p[0]];
};

int main()
{
    SFileHandler sf;
    sfile_init(&sf, NULL);

    printf("sizeof(sf)  : %ld\n", sizeof(sf));
    // printf("sf.root     : %p\n", sf.root);
    printf("sf.root[0]  : %p\n", sf.root->idx[0]);
    printf("sf.root[255]: %ld\n", (long int)sf.root->idx[259]);
    printf("============================\n");

    SFile_Key key = {.id = 0};
    ++key.id;

    SFile_SegDec segdec;
    sfile_get(&sf, &key, &segdec);
    // sfile_get(&sf, &key, &segdec);

    printf("offset: %.16lx\n", segdec.offset);
    printf("size  : %.16lx\n", segdec.size);

    // printf("==> %ld <==\n", sizeof(SFile_SegDec));
    // printf("==> %ld <==\n", sizeof(SFile_Page));
    // printf("==> %ld <==\n", sizeof(SFileHandler));
    // printf("sf.root size: %ld\n", sizeof(sf.root));

    return 0;
};

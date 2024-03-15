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

void sfile_init(SFileHandler *sf, const char *filename)
{
    sf->io = fopen(filename, "a+");
    sf->root = mallocIPage();
};

void sfile_release(SFileHandler *sf)
{
    // #TODO: free pages
    fclose(sf->io);
};

void sfile_get(SFileHandler *sf, SFile_Key *key, SFile_SegDec *segdec)
{
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

        SFile_Key _key = *key;
        _key.p[0] = 0;

        fflush(sf->io);
        fseek(sf->io, _key.id, SEEK_SET);
        fread(*o_ptr, sizeof(SFile_Page), 1, sf->io);
    };

    *segdec = ((SFile_Page *)*o_ptr)->idx[key->p[0]];
};

void sfile_add(SFileHandler *sf, SFile_SegDec *segdec, SFile_Key *key)
{
    printf("offset: %.16lx\n", segdec->offset);
    printf("size  : %.16lx\n", segdec->size);
    // #TODO:
};

void sfile_set(SFileHandler *sf, SFile_SegDec *segdec, SFile_Key *key)
{
    printf("offset: %.16lx\n", segdec->offset);
    printf("size  : %.16lx\n", segdec->size);
    // #TODO:
};

int main()
{

    SFileHandler sf;
    sfile_init(&sf, "./data..sfile_idx");

    printf("sizeof(sf)  : %ld\n", sizeof(sf));
    // printf("sf.root     : %p\n", sf.root);
    printf("sf.root[0]  : %p\n", sf.root->idx[0]);
    printf("sf.root[255]: %ld\n", (long int)sf.root->idx[255]);
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

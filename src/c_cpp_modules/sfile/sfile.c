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

SFile_SegDec *sfile_getsegdecptr(SFileHandler *sf, SFile_Key *key)
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

        fseek(sf->io, _key.id, SEEK_SET);
        fread(*o_ptr, sizeof(SFile_Page), 1, sf->io);
    };

    return &((SFile_Page *)*o_ptr)->idx[key->p[0]];
};

SFile_Key sfile_add(SFileHandler *sf, SFile_SegDec *segdec)
{
    fseek(sf->io, 0, SEEK_END);
    SFile_Key key = {.id = ftell(sf->io) / sizeof(SFile_SegDec)};
    fwrite(segdec, sizeof(SFile_SegDec), 1, sf->io);
    fflush(sf->io);
    *sfile_getsegdecptr(sf, &key) = *segdec;
    return key;
};

SFile_SegDec sfile_get(SFileHandler *sf, SFile_Key *key)
{
    return *sfile_getsegdecptr(sf, key);
};

bool sfile_set(SFileHandler *sf, SFile_Key *key, SFile_SegDec *segdec)
{
    fseek(sf->io, key->id * sizeof(SFile_SegDec), SEEK_SET);
    fwrite(segdec, sizeof(SFile_SegDec), 1, sf->io);
    *sfile_getsegdecptr(sf, key) = *segdec;
    // #TODO: if key were higher than the current highest key?
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

    printf("-------------------\n@sfile_get\n");
    segdec = sfile_get(&sf, &key);
    printf("offset: %.16lx\n", segdec.offset);
    printf("size  : %.16lx\n", segdec.size);

    printf("-------------------\n@sfile_add\n");
    key = sfile_add(&sf, &segdec);
    printf("Key: %d\n", key.id);

    // sfile_get(&sf, &key, &segdec);

    // printf("==> %ld <==\n", sizeof(SFile_SegDec));
    // printf("==> %ld <==\n", sizeof(SFile_Page));
    // printf("==> %ld <==\n", sizeof(SFileHandler));
    // printf("sf.root size: %ld\n", sizeof(sf.root));

    return 0;
};

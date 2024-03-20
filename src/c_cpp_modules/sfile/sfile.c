#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
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
    sf->io = fopen(filename, "r+");
    sf->root = mallocIPage();
};

void sfile_release(SFileHandler *sf)
{
    // #TODO: free pages
    fclose(sf->io);
};

SFile_SegDec *sfile_getsegdecptr(SFileHandler *sf, SFile_Key key)
{
    void **o_ptr = &(sf->root->idx[key.p[3]]);
    if (!*o_ptr)
        *o_ptr = mallocIPage();

    o_ptr = &(((SFile_IPage *)*o_ptr)->idx[key.p[2]]);
    if (!*o_ptr)
        *o_ptr = mallocIPage();

    o_ptr = &(((SFile_IPage *)*o_ptr)->idx[key.p[1]]);

    int8_t p0 = key.p[0];
    if (!*o_ptr)
    {
        *o_ptr = (SFile_Page *)malloc(sizeof(SFile_Page));
        if (!*o_ptr) // #TODO:
            abort();
        memset(*o_ptr, 0, sizeof(SFile_Page));

        key.p[0] = 0;
        fseek(sf->io, key.id, SEEK_SET);
        fread(*o_ptr, sizeof(SFile_Page), 1, sf->io);
    };

    return &((SFile_Page *)*o_ptr)->idx[p0];
};

SFile_Key sfile_add(SFileHandler *sf, SFile_SegDec *segdec)
{
    fseek(sf->io, 0, SEEK_END);
    SFile_Key key = {.id = ftell(sf->io) / sizeof(SFile_SegDec)};
    fwrite(segdec, sizeof(SFile_SegDec), 1, sf->io);
    fflush(sf->io);
    *sfile_getsegdecptr(sf, key) = *segdec;
    return key;
};

SFile_SegDec sfile_get(SFileHandler *sf, SFile_Key key)
{
    return *sfile_getsegdecptr(sf, key);
};

void sfile_set(SFileHandler *sf, SFile_Key key, SFile_SegDec *segdec)
{
    fseek(sf->io, key.id * sizeof(SFile_SegDec), SEEK_SET);
    fwrite(segdec, sizeof(SFile_SegDec), 1, sf->io);
    fflush(sf->io);
    *sfile_getsegdecptr(sf, key) = *segdec;
};

/*
 * Prefix tree indexing for file path
 */

/*
 * Database
 */

void segdb_init(struct segdb_handler *handler, const char *filename, size_t unit_size)
{
    FILE *stream;
    if (!(stream = fopen(filename, "r+")))
    {
        fclose(fopen(filename, "w"));
        stream = fopen(filename, "r+");
        if (!stream)
            abort(); // #TODO:
    };
    handler->stream = stream;

    size_t b = 1;
    while (b < unit_size)
        b <<= 1;
    handler->unit_size = b;

    // seek to end, make stream prepare the buffer then get filesize and buffsize
    fseek(stream, 0, SEEK_END);
    size_t filesize = ftello(stream);
    size_t buffsize = __fbufsize(stream);

    if (!b > buffsize)
        abort(); // #TODO: Error unit_size bigger than buffsize

    while (b <= buffsize)
        b <<= 1;
    handler->bufsize = b >> 1;

    size_t c = (filesize - 1) / handler->bufsize + 1;
    b = 1;
    while (b < c)
        b <<= 1;
    handler->ipage.size = b;

    b *= sizeof(size_t);
    memset(handler->ipage.idx = malloc(b), 0, b);
};

void segdb_release(struct segdb_handler *handler)
{
    handler->unit_size = 1;

    void *ptr;
    void **idx = handler->ipage.idx, **idx_max = idx + handler->ipage.size;
    do
    {
        if (!(ptr = *idx))
            free(ptr);
    } while (++idx < idx_max);

    free(handler->ipage.idx);
    handler->ipage.size = 0;

    fclose(handler->stream);
    handler->stream = NULL;
};

segdb_key segdb_add(struct segdb_handler *handler, void *blob)
{
    FILE *st = handler->stream;
    fseek(st, 0, SEEK_END);

    size_t u = handler->unit_size;
    segdb_key key = (ftell(st) - 1) / u + 1;
    fwrite(blob, u, 1, st);
    fflush(st);

    return key;
};

/* ---------------------- */

int main()
{
    struct segdb_handler ptreeHandler;
    segdb_init(&ptreeHandler, "./path_tree.idx", 9);
    segdb_release(&ptreeHandler);

    // SFileHandler sf;
    // sfile_init(&sf, "./data.db_idx");
    // // printf("buff size: %ld\n", __fbufsize(sf.io));

    // printf("sizeof(sf)  : %ld\n", sizeof(sf));
    // // printf("sf.root     : %p\n", sf.root);
    // printf("sf.root[0]  : %p\n", sf.root->idx[0]);
    // printf("sf.root[255]: %ld\n", (long int)sf.root->idx[255]);
    // printf("============================\n");

    // SFile_Key key = {.id = 0};
    // ++key.id;

    // SFile_SegDec segdec;

    // printf("-------------------\n@sfile_get\n");
    // segdec = sfile_get(&sf, key);
    // printf("offset: %.16lx\n", segdec.offset);
    // printf("size  : %.16lx\n", segdec.size);

    // printf("-------------------\n@sfile_add\n");
    // key = sfile_add(&sf, &segdec);
    // printf("Key: %d\n", key.id);

    // printf("-------------------\n@sfile_set\n");
    // key.id = 10;
    // segdec.offset = 16777215;
    // segdec.size = 6;
    // sfile_set(&sf, key, &segdec);
    // segdec = sfile_get(&sf, key);
    // printf("Key: %d\n", key.id);
    // printf("offset: %.16lx\n", segdec.offset);
    // printf("size  : %.16lx\n", segdec.size);

    return 0;
};

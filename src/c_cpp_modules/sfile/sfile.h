#include <stdio.h>   //size_t
#include <stdint.h>  //int8_t
#include <stdbool.h> //bool

/*
 * <name>          : data file
 * <name>.sfile_idx: Segmented indexing of <name>
 *    Always load/change/append file by a chunk of 1KB(32bit)/2KB(64bit)
 *
 * SFile_F_*: structure of blob in physical file
 */

// DB_Key = offset of SFile_F_SegDec in physical file
typedef struct
{
    size_t offset; // offset in .db file
    size_t size;
} SFile_SegDec;

/* intermediate page */
typedef struct SFile_IPage
{
    void *idx[256];
} SFile_IPage;

/* leaf page */
typedef struct SFile_Page
{
    SFile_SegDec idx[256];
} SFile_Page;

typedef union
{
    int32_t id;
    int8_t p[4];
} SFile_Key;

typedef struct SFileHandler
{
    FILE *io;
    SFile_IPage *root;
} SFileHandler;

typedef union
{
    int32_t id;
    int8_t p[4];
} db_key;

typedef struct strbuf
{
    void *buf;
    size_t size;
    size_t len; // defaulte = -1
} strbuf;

/* ---------------------- */
/* ruler unit loader */
struct rul_ipage
{
    void *idx[256]; // 2^8
};

/* SegmentLoader */
struct segdb_handler
{
    size_t unit_size;

    struct ipage
    {
        void *idx;    // indexes for intermediate pages
        size_t size; // always is a power of 2 and >= no. pages needed
    } ipage;

    FILE *stream;
    size_t bufsize;
};

typedef size_t segdb_key;
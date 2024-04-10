#include <stdlib.h> // malloc, realloc
#include <string.h> // memcmp, memcpy
#include "sbuf/sbuf.h"

static struct sbuf *sbuf_init()
{
    struct sbuf *sb = malloc(sizeof(struct sbuf));
    sb->h.alloc = sb->h.size = 0;
    sb->buf = NULL;
    sb->independence = true;
    return sb;
};

struct sbuf *sbuf_alloc(size_t alloc)
{
    // alloc = --alloc - (alloc % sizeof(size_t)) + sizeof(size_t);
    struct sbuf *sb = sbuf_init();
    sb->h.alloc = 0;
    sb->h.alloc = alloc;
    sb->buf = alloc ? malloc(alloc) : NULL;
    return sb;
};

void sbuf_free(struct sbuf *const restrict sb)
{
    if (!sb || !sb->independence)
        return;
    if (sb->buf)
        free(sb->buf);
    free(sb);
};

void sbuf_realloc(struct sbuf *const restrict sb, size_t alloc)
{
    // alloc = --alloc - (alloc % sizeof(size_t)) + sizeof(size_t);
    if (alloc > sb->h.alloc)
    {
        if (sb->h.size > alloc)
            sb->h.size = alloc;

        void *new_buf = memcpy(malloc(sb->h.alloc = alloc), sb->buf, sb->h.size);
        free(sb->buf);
        sb->buf = new_buf;
    };
};

void *sbuf_detach(struct sbuf *const restrict sb){
    
};

void sbuf_push(struct sbuf *const restrict sb, void *buf, const size_t size)
{
    sbuf_realloc(sb, sb->h.size + size);
    memcpy(sb->buf + sb->h.size, buf, size);
};

size_t sbuf_pop(struct sbuf *const restrict sb, void *buf, size_t size)
{
    if (size > sb->h.size)
    {
        size = sb->h.size;
        sb->h.size = 0;
    };
    memcpy(buf, sb->buf + sb->h.size, size);
    return size;
};

void sbuf_trim(struct sbuf *const restrict sb, const size_t size)
{
    if ((sb->h.size -= size) < 0)
        sb->h.size = 0;
};

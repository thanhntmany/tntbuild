#include <stdlib.h> // malloc, realloc
#include <string.h> // memcmp, memcpy
#include "sbuf/sbuf.h"

struct sbuf *sbuf_init()
{
    struct sbuf *sb = malloc(sizeof(struct sbuf));
    sb->h.alloc = sb->h.size = 0;
    sb->buf = NULL;
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
    if (sb->buf)
        free(sb->buf);
    free(sb);
};

/* Require the alloc size. Realloc if needed. */
void sbuf_reqalloc(struct sbuf *const restrict sb, size_t alloc)
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

void sbuf_push(struct sbuf *const restrict sb, void *buf, const size_t size)
{
    sbuf_reqalloc(sb, sb->h.size + size);
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

struct sbuf *sbuf_from_str(const char *str)
{
    size_t len = strlen(str) + 1;
    struct sbuf *sb = sbuf_alloc(len);
    memcpy(sb->buf, str, len);
    sb->h.size = len - 1;
    return sb;
};

char *sbuf_as_str(struct sbuf *const restrict sb)
{
    sbuf_reqalloc(sb, sb->h.size + 1);
    *(char *)(sb->buf + sb->h.size) = '\0';
    return sb->buf;
};

struct sbuf *sbuf_dup(struct sbuf *const restrict sb)
{
    struct sbuf *_sb = sbuf_alloc(sb->h.alloc);
    memcpy(_sb->buf, sb->buf, _sb->h.size = sb->h.size);
    return _sb;
};

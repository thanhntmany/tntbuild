#include <stdlib.h> // malloc, free
#include <string.h> // strlen, memcpy, memset
#include "strbuf.h"

/*
 * Basic initiating and freeing instances
 */

struct strbuf *strbuf(const size_t size)
{
    struct strbuf *restrict sb = malloc(sizeof(struct strbuf));
    sb->buf = malloc(sb->alloc = (size < 1 ? 1 : size));
    sb->len = 0;
    return sb;
};

struct strbuf *strbuf_from(const char *restrict buf, const size_t len, const size_t ex)
{
    struct strbuf *restrict sb = malloc(sizeof(struct strbuf));
    sb->len = len;
    sb->buf = malloc(sb->alloc = len + ex);
    memcpy(sb->buf, buf, len);
    return sb;
};

void strbuf_load(struct strbuf *restrict sb, const size_t offset, const char *restrict buf, const size_t len)
{
    size_t end = offset + len;
    if (sb->len < end)
        if ((sb->len = end) >= sb->alloc)
            sb->buf = realloc(sb->buf, sb->alloc = sb->len);

    memcpy(sb->buf + offset, buf, len);
};

void strbuf_memset(struct strbuf *restrict sb, const int c, const size_t start, const size_t count)
{
    size_t end = start + count;
    if (sb->len < end)
        if ((sb->len = end) >= sb->alloc)
            sb->buf = realloc(sb->buf, sb->alloc = sb->len);

    memset(sb->buf + start, c, count);
};

void strbuf_clear(struct strbuf *restrict sb)
{
    sb->len = 0;
};

void strbuf_free(struct strbuf *restrict sb)
{
    free(sb->buf);
    free(sb);
};

/*
 * I/O with string
 */

char *strbuf_asstr(struct strbuf *restrict sb)
{
    if (sb->len >= sb->alloc)
        sb->buf = realloc(sb->buf, sb->alloc = sb->len + 1);

    sb->buf[sb->len] = '\0'; // null-terminated
    return sb->buf;
};

char *strbuf_tostr(struct strbuf *restrict sb)
{
    char *restrict str = malloc(sb->len + 1);
    memcpy(str, sb->buf, sb->len);
    str[sb->len] = '\0'; // null-terminated
    return str;
};

/*
 * File System
 */

void strbuf_getcwd(const struct strbuf *sb){};
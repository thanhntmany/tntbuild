#include <stdlib.h> // malloc, free
#include <string.h> // strlen, memcpy, memset
#include "strbuf.h"

struct strbuf *strbuf_init(size_t size)
{
    // if (size < 1) {
    //     // #TODO: Error handling
    //     // size must be greater than 0
    // };
    struct strbuf *sb = malloc(sizeof(struct strbuf));
    sb->buf = malloc(sb->alloc = size);
    sb->len = 0;
    return sb;
};

void strbuf_clear(struct strbuf *sb)
{
    sb->len = 0;
};

void strbuf_free(struct strbuf *sb)
{
    free(sb->buf);
    free(sb);
};

/*
 * Buffer
 */

void strbuf_memset(struct strbuf *sb, int c, size_t start, size_t count)
{
    if (sb->alloc < start)
        return;

    if (count > sb->alloc - start)
        count = sb->alloc - start;

    memset(sb->buf + start, c, count);
};

void strbuf_cmp(){
    // #TODO: int memcmp (const void *a1, const void *a2, size_t size)
};

void strbuf_copy(struct strbuf *dst, struct strbuf *src)
{
    if (dst->alloc <= src->len)
    {
        free(dst->buf);
        dst->buf = malloc(dst->alloc = src->len + 1);
    };
    memcpy(dst->buf, src->buf, dst->len = src->len);
};

void strbuf_concat(){
    // #TODO: concat multi strbuf
};
void strbuf_endsWith(){
    // #TODO:
};
void strbuf_startsWith(){
    // #TODO:
};

/*
 * String
 */

struct strbuf *strbuf_loadstr(struct strbuf *sb, char *str)
{
    sb->len = strlen(str);
    if (sb->len >= sb->alloc)
        sb->buf = malloc(sb->alloc = sb->len + 1);
    memcpy(sb->buf, str, sb->len + 1);
    return sb;
};

char *strbuf_asstr(struct strbuf *sb)
{
    sb->buf[sb->len] = '\0'; // null-terminated
    return sb->buf;
};

char *strbuf_tostr(struct strbuf *sb)
{
    char *str = malloc(sb->len + 1);
    memcpy(str, sb->buf, sb->len);
    str[sb->len] = '\0'; // null-terminated
    return str;
};

/*
 * File System
 */

void strbuf_getcwd(){};
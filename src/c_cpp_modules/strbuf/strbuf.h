#ifndef STRBUF_H
#define STRBUF_H

#include <fcntl.h>  // flock, off_t
#include <stddef.h> // size_t

/**************************************
 * segbuf
 */

struct strbuf
{
    size_t alloc;

    size_t len;
    void *buf;
};

struct strbuf *strbuf_alloc(size_t len);
void strbuf_free(struct strbuf *const sb);
struct strbuf *strbuf_view(struct strbuf *const sb, off_t start, size_t len);

#endif
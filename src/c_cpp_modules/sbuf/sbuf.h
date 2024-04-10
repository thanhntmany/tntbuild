#ifndef SBUF_H
#define SBUF_H

#include <stddef.h> // size_t
#include <fcntl.h>  // off_t
#include "sbufio.h" // off_t

/**************************************
 * segbuf
 */

struct __attribute__((packed)) sbuf_header
{
    size_t alloc; // `alloc` is always increased, never decreased.
    size_t size;  // `used` always < `size`
};

struct sbuf
{
    struct sbuf_header h;
    void *buf;
    bool independence;
};

static struct sbuf *sbuf_init();
struct sbuf *sbuf_alloc(size_t alloc);
void sbuf_free(struct sbuf *const restrict sb);
void sbuf_realloc(struct sbuf *const restrict sb, size_t alloc);

void sbuf_push(struct sbuf *const restrict sb, void *buf, const size_t size);
size_t sbuf_pop(struct sbuf *const restrict sb, void *buf, size_t size);
void sbuf_trim(struct sbuf *const restrict sb, const size_t size);

/* Operations */
void sbuf_pwd();
void sbuf_concat();
void sbuf_substr();
void sbuf_load_str();
void sbuf_as_str();
void sbuf_to_str();

#endif
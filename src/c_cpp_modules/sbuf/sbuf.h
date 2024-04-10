#ifndef SBUF_H
#define SBUF_H

#include <fcntl.h>   // off_t
#include <stdbool.h> // bool
#include <stddef.h>  // size_t

/**************************************
 * segbuf
 */

struct __attribute__((packed)) sbuf_header
{
    size_t alloc; // `alloc`: const
    size_t size;  // `used` always < `size`
};

struct sbuf
{
    struct sbuf_header h;
    void *buf;
    bool independence;
};

struct sbuf *sbuf_init();
struct sbuf *sbuf_alloc(size_t alloc);
void sbuf_free(struct sbuf *const restrict sb);
void sbuf_reqalloc(struct sbuf *const restrict sb, size_t alloc);

void sbuf_push(struct sbuf *const restrict sb, void *buf, const size_t size);
size_t sbuf_pop(struct sbuf *const restrict sb, void *buf, size_t size);
void sbuf_trim(struct sbuf *const restrict sb, const size_t size);

/* Operations */
struct sbuf *sbuf_from_str(const char *str);
// void sbuf_load_str();
char *sbuf_as_str(struct sbuf *const restrict sb);
void sbuf_to_str();
void sbuf_pwd();
void sbuf_concat();
void sbuf_substr();
struct sbuf *sbuf_dup(struct sbuf *const restrict sb);

#endif
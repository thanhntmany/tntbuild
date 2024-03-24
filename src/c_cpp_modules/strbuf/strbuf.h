#ifndef STRBUF_H
#define STRBUF_H

#include <stddef.h>

/*
 * Inspired by https://raw.githubusercontent.com/git/git/master/strbuf.h
 *
 * Strbuf is a low-level primitive. It caches the length of string and
 * allocation size of buffer to optimize operations.
 */

/*
 * ### NOTE: This is NOT null-terminated.
 *
 * This is the string buffer structure.
 * `buf`  : ponter to the buffer (string itself)
 * `len`  : the current length of the string/data
 * `alloc`: the size of alloced buffer. (always > `len`)
 */
struct strbuf
{
	char *buf;
	size_t len;
	size_t alloc;
};

struct strbuf *strbuf(const size_t size);

struct strbuf *strbuf_from(const char *restrict buf, const size_t len, const size_t ex);

void strbuf_load(struct strbuf *restrict sb, const size_t offset, const char *restrict buf, const size_t len);

void strbuf_memset(struct strbuf *restrict sb, const int c, const size_t start, const size_t count);

void strbuf_clear(struct strbuf *restrict sb);

void strbuf_free(struct strbuf *restrict sb);

/*
 * I/O with string
 */

char *strbuf_asstr(struct strbuf *restrict sb);

char *strbuf_tostr(struct strbuf *restrict sb);

/*
 * File System
 */

void strbuf_getcwd(const struct strbuf *sb);

#endif

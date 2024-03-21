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
 * `len`  : the current length of the string
 * `alloc`: the size of alloced buffer. (always > `len`)
 */
struct strbuf
{
	char *buf;
	size_t len;
	size_t alloc;
};

/* # NOTE: Use strbuf_free() to free instance after using */
struct strbuf *strbuf_init(size_t size);

/* free internal buff and remove strbuf instance*/
void strbuf_free(struct strbuf *sb);

void strbuf_clear(struct strbuf *sb);

/*
 * Buffer
 */

void strbuf_memset(struct strbuf *sb, int c, size_t start, size_t count);

/*
 * String
 */

struct strbuf *strbuf_loadstr(struct strbuf *sb, char *str);

char *strbuf_asstr(struct strbuf *sb);

/* # NOTE: Use free() to free this (char *) after using */
char *strbuf_tostr(struct strbuf *sb);

#endif

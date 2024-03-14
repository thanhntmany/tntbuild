#ifndef STRBUF_H
#define STRBUF_H

#include <stddef.h>

/*
 * Inspired by https://raw.githubusercontent.com/git/git/master/strbuf.h
 *
 * Strbuf is a low-level primitive. It caches the length of string and
 * allocation size of buffer to optimize operations.
 */

/**
 * This is the string buffer structure. The `len` member can be used to
 * determine the current length of the string, and `buf` member provides
 * access to the string itself.
 */
typedef struct
{
	char *buf;
	size_t alloc;
	size_t len;
} strbuf;

extern char strbuf_slopbuf[];
#define STRBUF_INIT           \
	{                         \
		.buf = strbuf_slopbuf \
	}

#endif

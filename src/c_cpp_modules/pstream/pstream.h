#ifndef PSTREAM_H
#define PSTREAM_H

#include <stdio.h>   // size_t
#include <stdint.h>  // int8_t
#include <stdbool.h> // bool
#include <sys/uio.h> // struct iovec
#include <fcntl.h>   // struct flock

/* file mapping */
struct pstream_page
{
    off_t offset;
    struct pstream_page *prev;
    struct pstream_page *next;
    struct iovec iovec;
    bool changed;
};

struct pstream
{
    struct pstream_page *pages_head; // linked list
    off_t page_size;
    size_t pool_size; // need init before open
    int __page_count;
    int page_max;
    int filedes;
    struct flock flock;
};

/* Functions */

/* NOTE: You must specify pool_size before call pstream_open.
 *
 * E.g: struct pstream ps = {.pool_size = 1048576}; // 1MB
 * if pool_size=0, use default: 512 MB.
 */
int pstream_open(struct pstream *ps, const char *filename);

void pstream_lockwrite(struct pstream *ps);

void pstream_unlockwrite(struct pstream *ps);

void pstream_read(struct pstream *ps, off_t offset, void *buffer, size_t nbyte);

void pstream_write(struct pstream *ps, off_t offset, const void *buffer, size_t nbyte);

void pstream_flush(struct pstream *ps);

void pstream_clear(struct pstream *ps);

int pstream_close(struct pstream *ps);

#endif

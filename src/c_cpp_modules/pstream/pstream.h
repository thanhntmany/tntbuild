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
    int __page_count;
    int page_max;
    int filedes;
    struct flock flock;
};

/* Functions */

/* NOTE: You must specify pool_size before call pstream_open.
 *
 * `poolsize` is in bytes.
 * if poolsize=0, use default: poolsize = the size of the file
 */
struct pstream *pstream_open(const char *filename, size_t poolsize);

void pstream_lock(struct pstream *ps);

void pstream_read(struct pstream *ps, off_t offset, void *buffer, size_t nbyte);

void pstream_write(struct pstream *ps, off_t offset, const void *buffer, size_t nbyte);

void pstream_flush(struct pstream *ps);

void pstream_unlock(struct pstream *ps);

void pstream_clear(struct pstream *ps);

void pstream_close(struct pstream *ps);

#endif

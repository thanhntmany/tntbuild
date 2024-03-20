#ifndef PSTREAM_H
#define PSTREAM_H

#include <stdio.h>   //size_t
#include <stdint.h>  //int8_t
#include <stdbool.h> //bool
#include <sys/uio.h> //iovec

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
};

/* Functions */
int pstream_open(struct pstream *ps, const char *filename, off_t max_byte);
ssize_t pstream_read(struct pstream *ps, off_t offset, void *buffer, size_t nbyte);
ssize_t pstream_write(struct pstream *ps, off_t offset, const void *buffer, size_t nbyte);
int pstream_flush(struct pstream *ps);
int pstream_clear(struct pstream *ps);
int pstream_close(struct pstream *ps);
int pstream_close(struct pstream *ps);

#endif

#ifndef PSTREAM_H
#define PSTREAM_H

#include <stdio.h>   //size_t
#include <stdint.h>  //int8_t
#include <stdbool.h> //bool
#include <sys/uio.h> //iovec

/* file mapping */
struct pstream_page
{
    struct iovec iovec;
    off_t offset;
    size_t len; /* Length of data. */
    struct pstream_page *prev;
    struct pstream_page *next;
    bool changed;
};

struct pstream
{
    struct pstream_page *pages_head; // linked list
    off_t page_size;
    off_t __file_size;
    int filedes;
};


/* Functions */
int pstream_close(struct pstream *ps);

#endif
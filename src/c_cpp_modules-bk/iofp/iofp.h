#ifndef IOFP_H
#define IOFP_H

#include <sys/file.h> // off_t
#include <stdbool.h>  // bool
#include <stddef.h>   // size_t

struct iofp_page
{
    off_t offset;
    void *buff; /* Pointer to data.  */
    struct iofp_page *prev;
    struct iofp_page *next;
    bool changed;
};

struct iofp_io
{
    const char *filepath;
    int fd;
    struct flock flock;
    size_t block_size;
};

struct iofp_opt
{
    size_t page_size;       // bytes
    size_t flush_threshold; // bytes
};

struct iofp
{
    struct iofp_page anchor; // .iofp_buffofpage is always NULL, .offset alway < 0 (-1)
    size_t count;
    size_t page_size;       // bytes
    size_t flush_threshold; // quantity of pages

    struct iofp_io io;
};

struct iofp *iofp_open(const char *const restrict filename);
void iofp_setotp(struct iofp *const restrict fp, const struct iofp_opt *const restrict otp);
void iofp_flush(struct iofp *const restrict fp);
void iofp_clear(struct iofp *const restrict fp);
void iofp_close(struct iofp *const restrict fp);

void *iofp_locate(struct iofp *const restrict fp, const off_t offset, struct iofp_page **found_page);
off_t iofp_offsettoptr(struct iofp *const restrict fp, void *const restrict ptr, struct iofp_page **found_page);
void iofp_read(struct iofp *const restrict fp, off_t offset, void *restrict buffer, size_t nbyte);
void iofp_write(struct iofp *const restrict fp, off_t offset, void *restrict buffer, size_t nbyte);

#endif
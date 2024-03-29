#ifndef SFIO_H
#define SFIO_H

#include <sys/file.h> // off_t
#include <sys/uio.h>  // iovec
#include <stdbool.h>  // bool

struct iofp_page
{
    struct iovec iovec;
    struct iofp_page *prev;
    struct iofp_page *next;
    off_t offset;
    bool changed;
};
#define iofp_buffofpage(page) (page)->iovec.iov_base
#define iofp_markpagechanged(page) page->changed = true

struct iofp_opt
{
    size_t page_size; // bytes
    size_t keep;     // bytes
    size_t flush;     // bytes
};

struct iofp
{
    struct iofp_page anchor_page;
    size_t page_size;
    size_t _page_count;
    struct iofp_threshold
    {
        size_t keep; // quantity of pages
        size_t flush; // quantity of pages
    } threshold;
    int fd;
    struct flock flock;
};

struct iofp *iofp_open(const char *const restrict filename); // open, lock
void iofp_setotp(struct iofp *const restrict fp, const struct iofp_opt *const restrict otp);
void iofp_flush(struct iofp *const restrict fp); // flush changed pages
void iofp_clear(struct iofp *const restrict fp); // free unchanged pages
void iofp_close(struct iofp *const restrict fp); // flush, clear, unlock, close

void *iofp_ptrtooffset(struct iofp *const restrict fp, const off_t offset, struct iofp_page **found_page);
off_t iofp_offsettoptr(struct iofp *const restrict fp, void *const restrict ptr, struct iofp_page **found_page);
off_t iofp_toendofpage(struct iofp *const restrict fp, const off_t offset);

void iofp_read(struct iofp *const restrict fp, off_t offset, void *restrict buffer, size_t nbyte);
void iofp_write(struct iofp *const restrict fp, off_t offset, void *restrict buffer, size_t nbyte);

#endif
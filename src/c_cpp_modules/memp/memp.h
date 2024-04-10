#ifndef MEMP_H
#define MEMP_H

#include <sys/file.h> // off_t
#include <stdbool.h>  // bool

struct memp_page
{
    off_t offset;
    void *buff; /* Pointer to data.  */
    struct memp_page *prev;
    struct memp_page *next;
    int nref;
};

struct memp_opt
{
    size_t page_size; // bytes
};

struct memp
{
    struct memp_page anchor; // .buff is always NULL, .offset alway < 0 (-1)
    size_t page_size;
};

struct memp *memp_open(); // init handler
void memp_setotp(struct memp *const restrict mp, const struct memp_opt *const restrict otp);
void memp_clear(struct memp *const restrict mp);
void memp_close(struct memp *const restrict mp);

void *memp_locate(struct memp *const restrict mp, const off_t offset, struct memp_page **found_page);
off_t memp_locate_ptr(struct memp *const restrict mp, void *const restrict ptr, struct memp_page **found_page);
#define memp_toendofpage(fp, offset) (fp->page_size - (offset % fp->page_size))
void memp_free_page(struct memp *const restrict mp, struct memp_page *page);

void memp_read(struct memp *const restrict mp, off_t offset, void *restrict buffer, size_t nbyte);
void memp_write(struct memp *const restrict mp, off_t offset, void *restrict buffer, size_t nbyte);

#endif
#include <errno.h>    // errno
#include <fcntl.h>    // open, F_WRLCK, , F_SETLK
#include <stdlib.h>   // malloc, free
#include <sys/stat.h> // S_IRUSR, S_IWUSR
#include <unistd.h>   // close, SEEK_SET, sysconf, _SC_PAGESIZE, ssize_t
#include <string.h>   // memcpy
#include <sys/uio.h>  // iovec, preadv
#include <malloc.h>   // memalign
#include "memp.h"

/**************************************
 * page
 */

static struct memp_page *page_init(struct memp *const restrict mp, const off_t page_offset)
{
    struct memp_page *page = malloc(sizeof(struct memp_page));
    register size_t page_size = mp->page_size;
    page->offset = page_offset;
    page->buff = memalign(page_size, page_size);
    page->nref = 0;

    return page;
};

static void page_clear(struct memp *const restrict mp, struct memp_page *page)
{
    memset(page->buff, 0, mp->page_size);
};

static void page_free(struct memp_page *page)
{
    free(page->buff);
    free(page);
};

/******************************************************************************
 *
 * Main functions
 *
 */
static struct memp_opt PMEM_DEFAULT_OPT = {.page_size = 0};
struct memp *memp_open()
{
    struct memp *const restrict mp = malloc(sizeof(struct memp));

    mp->anchor.offset = -1;
    mp->anchor.next = mp->anchor.prev = &mp->anchor;
    mp->anchor.buff = NULL;

    memp_setotp(mp, &PMEM_DEFAULT_OPT);

    return mp;
};

void memp_setotp(struct memp *const restrict mp, const struct memp_opt *const restrict otp)
{
    // page_size
    size_t page_size = otp->page_size;
    size_t sc_pagesize = (size_t)sysconf(_SC_PAGESIZE);
    if (page_size < sc_pagesize)
        page_size = sc_pagesize;

    register size_t ps = 512;
    while (ps < page_size)
        ps <<= 1;

    if (mp->page_size != ps)
    {
        memp_clear(mp);
        mp->page_size = ps;
    };
};

void memp_free_page(struct memp *const restrict mp, struct memp_page *page)
{
    (page->prev->next = page->next)->prev = page->prev;
    page_free(page);
};

void memp_clear(struct memp *const restrict mp)
{
    struct memp_page *page = &mp->anchor;
    while ((page = page->next)->buff)
        page_free(page);
};

void memp_close(struct memp *const restrict mp)
{
    memp_clear(mp);
    free(mp);
};

void *memp_locate(struct memp *const restrict mp, const off_t offset, struct memp_page **found_page)
{
    const off_t p_offset = offset % mp->page_size, page_offset = offset - p_offset;
    struct memp_page *restrict page = mp->anchor.next;
    if (page->offset != page_offset) // if not first page
    {
        register off_t o;
        while ((o = (page = page->next)->offset) != page_offset)
            if (o < 0)
            {
                page = page_init(mp, page_offset);
                page_clear(mp, page);
                goto retpage;
            };
        (page->prev->next = page->next)->prev = page->prev;

    retpage:
        (((page->next = mp->anchor.next)->prev = page)->prev = &mp->anchor)->next = page; // move page to the first position
    };
    return (*found_page = page)->buff + p_offset;
};

off_t memp_locate_ptr(struct memp *const restrict mp, void *const restrict ptr, struct memp_page **found_page)
{
    const size_t page_size = mp->page_size;
    struct memp_page *page = &mp->anchor;
    size_t _p;
    void *buff;

    while ((buff = (page = page->next->buff)))
        if (ptr >= buff && (_p = ptr - buff) < page_size)
        {
            // move page to the first position
            (page->prev->next = page->next)->prev = page->prev;
            (((page->next = mp->anchor.next)->prev = page)->prev = &mp->anchor)->next = page;
            return (*found_page = page)->offset + _p;
        };

    *found_page = NULL;
    return -1;
};

void memp_read(struct memp *const restrict mp, off_t offset, void *restrict buffer, size_t nbyte)
{
    const off_t page_size = mp->page_size;
    struct memp_page *page;
    void *ptr;
    off_t load;
    while (nbyte)
    {
        ptr = memp_locate(mp, offset, &page);
        if ((load = page->buff + page_size - ptr) > nbyte)
            load = nbyte;
        memcpy(buffer, ptr, load);
        offset += load;
        buffer += load;
        nbyte -= load;
    };
};

void memp_write(struct memp *const restrict mp, off_t offset, void *restrict buffer, size_t nbyte)
{
    const off_t page_size = mp->page_size;
    struct memp_page *page;
    void *ptr;
    off_t load;
    while (nbyte)
    {
        ptr = memp_locate(mp, offset, &page);
        if ((load = page->buff + page_size - ptr) > nbyte)
            load = nbyte;
        memcpy(ptr, buffer, load);
        offset += load;
        buffer += load;
        nbyte -= load;
    };
};

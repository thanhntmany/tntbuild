#include <errno.h>    // errno
#include <fcntl.h>    // open, F_WRLCK, F_UNLCK, F_SETLK
#include <stdlib.h>   // malloc, free
#include <sys/stat.h> // S_IRUSR, S_IWUSR
#include <unistd.h>   // close, SEEK_SET, sysconf, _SC_PAGESIZE, ssize_t
#include <string.h>   // memcpy
#include "iofp.h"

#include <stdio.h>

static struct iofp_page *load_page(struct iofp *const restrict fp, const off_t page_offset)
{
    struct iofp_page *page = malloc(sizeof(struct iofp_page));
    register size_t page_size = page->iovec.iov_len = fp->page_size;
    iofp_buffofpage(page) = aligned_alloc(page_size, page_size);

    preadv(fp->fd, &page->iovec, 1, page->offset = page_offset); // #TODO: Error handling
    page->changed = false;

    if (++fp->_page_count >= fp->threshold.flush) {
        // #TODO:
    };

    return page;
};

static struct iofp_page *page_at(struct iofp *const restrict fp, const off_t page_offset)
{
    struct iofp_page *restrict page = fp->anchor_page.next;
    if (iofp_buffofpage(page) && page->offset == page_offset) // first page
        return page;
    while (iofp_buffofpage(page = page->next))
        if (page->offset == page_offset)
        {
            (page->prev->next = page->next)->prev = page->prev;
            goto ret;
        };
    page = load_page(fp, page_offset);

ret:
    // place page at the first page position and return it.
    return (((page->next = fp->anchor_page.next)->prev = page)->prev = &fp->anchor_page)->next = page;
};

void save_page(struct iofp *const restrict fp, struct iofp_page *const restrict page)
{
    printf("save_page: %ld\n", page->offset);
    pwritev(fp->fd, &page->iovec, 1, page->offset); // #TODO: Error handling
    page->changed = false;
};

void free_page(struct iofp_page *page)
{
    if (!iofp_buffofpage(page))
        return;
    if (page->prev)
        page->prev->next = page->next;
    if (page->next)
        page->next->prev = page->prev;
    free(iofp_buffofpage(page));
    free(page);
};

static struct flock IOFP_FLOCK = {.l_whence = SEEK_SET, .l_start = 0, .l_len = 0};

/******************************************************************************
 *
 * Main functions
 *
 */
static struct iofp_opt IOFP_DEFAULT_OPT = {.page_size = 0, .keep = 0, .flush = 0};
struct iofp *iofp_open(const char *const restrict filename)
{
    // Init handler
    struct iofp *const restrict fp = malloc(sizeof(struct iofp));
    fp->fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    // Init page list
    fp->anchor_page.offset = -1;
    fp->anchor_page.next = fp->anchor_page.prev = &fp->anchor_page;
    fp->anchor_page.iovec.iov_base = NULL;
    fp->anchor_page.iovec.iov_len = 0;

    // Init lock, lock write (+read)
    fp->flock = IOFP_FLOCK;
    fp->flock.l_type = F_WRLCK;
    fcntl(fp->fd, F_SETLKW, &fp->flock);

    iofp_setotp(fp, &IOFP_DEFAULT_OPT);

    return fp;
};

void iofp_setotp(struct iofp *const restrict fp, const struct iofp_opt *const restrict otp)
{
    // page_size
    size_t page_size = otp->page_size;
    if (page_size < 512)
    {
        struct stat st;
        fstat(fp->fd, &st); // #TODO: error handling
        page_size = (size_t)st.st_blksize;
    };

    register size_t ps = 512;
    while (ps < page_size)
        ps <<= 1;

    if (fp->page_size != ps)
    {
        fp->page_size = ps;
        // #TODO: flush all, clear all keepd pages here
        fp->_page_count = 0;
    };

    // threshold.keep
    ps <<= 1;
    fp->threshold.keep = (otp->keep < ps ? ps : otp->keep) / ps;

    // threshold.flush
    ps <<= 1;
    fp->threshold.flush = (otp->flush < ps ? ps : otp->flush) / ps;
};

void iofp_flush(struct iofp *const restrict fp)
{
    struct iofp_page *page = fp->anchor_page.next;
    while (iofp_buffofpage(page))
    {
        if (page->changed)
            save_page(fp, page);
        page = page->next;
    };
};

void iofp_close(struct iofp *const restrict fp)
{
    iofp_flush(fp);
    close(fp->fd);
    free(fp);
};

void *iofp_ptrtooffset(struct iofp *const restrict fp, const off_t offset, struct iofp_page **found_page)
{
    const size_t page_size = fp->page_size;
    const off_t p_offset = offset % page_size;
    return p_offset + iofp_buffofpage(*found_page = page_at(fp, offset - p_offset));
};

off_t iofp_offsettoptr(struct iofp *const restrict fp, void *const restrict ptr, struct iofp_page **found_page)
{
    const size_t page_size = fp->page_size;
    struct iofp_page *page = &fp->anchor_page;
    size_t _p;
    void *buff;

    while ((buff = iofp_buffofpage(page = page->next)))
        if (ptr >= buff && (_p = ptr - buff) < page_size)
            return (*found_page = page)->offset + _p;

    return -1;
};

off_t iofp_toendofpage(struct iofp *const restrict fp, const off_t offset)
{
    register size_t ps = fp->page_size;
    return ps - (offset % ps);
};

void iofp_read(struct iofp *const restrict fp, off_t offset, void *restrict buffer, size_t nbyte)
{
    const off_t page_size = fp->page_size;
    struct iofp_page *page;
    void *ptr;
    off_t load;
    while (nbyte)
    {
        ptr = iofp_ptrtooffset(fp, offset, &page);
        if ((load = iofp_buffofpage(page) + page_size - ptr) > nbyte)
            load = nbyte;
        memcpy(buffer, ptr, load);
        offset += load;
        buffer += load;
        nbyte -= load;
    };
};

void iofp_write(struct iofp *const restrict fp, off_t offset, void *restrict buffer, size_t nbyte)
{
    const off_t page_size = fp->page_size;
    struct iofp_page *page;
    void *ptr;
    off_t load;
    while (nbyte)
    {
        ptr = iofp_ptrtooffset(fp, offset, &page);
        if ((load = iofp_buffofpage(page) + page_size - ptr) > nbyte)
            load = nbyte;
        iofp_markpagechanged(page);
        memcpy(ptr, buffer, load);
        offset += load;
        buffer += load;
        nbyte -= load;
    };
};

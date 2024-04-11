#include <errno.h>    // errno
#include <fcntl.h>    // open, F_WRLCK, , F_SETLK
#include <stdlib.h>   // malloc, free
#include <sys/stat.h> // S_IRUSR, S_IWUSR
#include <unistd.h>   // close, SEEK_SET, sysconf, _SC_PAGESIZE, ssize_t
#include <string.h>   // memcpy, strlen
#include <sys/uio.h>  // iovec, preadv
#include <malloc.h>   // memalign
#include "iofp.h"

/**************************************
 * I/O
 */

static struct flock IOFP_FLOCK = {.l_whence = SEEK_SET, .l_start = 0, .l_len = 0};

static void io_init(struct iofp_io *const restrict io, const char *const restrict filepath)
{
    size_t path_size = strlen(filepath);
    io->filepath = malloc(path_size + 1);
    memcpy((void *restrict)io->filepath, filepath, path_size + 1);

    // Init lock, lock write (+read)
    io->fd = open(filepath, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    struct stat st;
    fstat(io->fd, &st); // #TODO: error handling
    io->block_size = (size_t)st.st_blksize;

    io->flock = IOFP_FLOCK;
    io->flock.l_type = F_WRLCK;
    fcntl(io->fd, F_SETLKW, &io->flock);
};

static void io_close(struct iofp_io *const restrict io)
{
    io->flock.l_type = F_UNLCK;
    fcntl(io->fd, F_SETLKW, &io->flock);

    free((void *restrict)io->filepath);
    close(io->fd);
};

static int io_read_page(struct iofp_io *const restrict io, off_t offset, void *const restrict buf, size_t page_size)
{
    struct iovec iov = {.iov_len = page_size, .iov_base = buf};
    return preadv(io->fd, &iov, 1, offset); // #TODO: Error handling
};

static int io_write_page(struct iofp_io *const restrict io, off_t offset, void *const restrict buf, size_t page_size)
{
    struct iovec iov = {.iov_len = page_size, .iov_base = buf};
    return pwritev(io->fd, &iov, 1, offset); // #TODO: Error handling
};

/**************************************
 * page_*
 */

static struct iofp_page *page_gen(struct iofp *const restrict fp)
{
    struct iofp_page *page = malloc(sizeof(struct iofp_page));
    page->buff = memalign(fp->page_size, fp->page_size);
    page->next = page->prev = page;
    page->changed = false;
    return page;
};

static void page_free(struct iofp_page *page)
{
    free(page->buff);
    free(page);
};

/**************************************
 *
 * Main functions
 *
 */

static struct iofp_opt IOFP_DEFAULT_OPT = {.page_size = 0, .flush_threshold = 0};

struct iofp *iofp_open(const char *const restrict filename)
{
    struct iofp *const restrict fp = malloc(sizeof(struct iofp));

    io_init(&fp->io, filename);

    fp->page_size = (size_t)sysconf(_SC_PAGESIZE);
    fp->count = 0;
    fp->anchor.offset = -1;
    fp->anchor.next = fp->anchor.prev = &fp->anchor;
    fp->anchor.buff = NULL;
    fp->anchor.changed = false;

    iofp_setotp(fp, &IOFP_DEFAULT_OPT);
    return fp;
};

void iofp_setotp(struct iofp *const restrict fp, const struct iofp_opt *const restrict otp)
{
    // page_size
    size_t page_size = otp->page_size;
    if (page_size < fp->io.block_size)
        page_size = fp->io.block_size;

    register size_t ps = 512;
    while (ps < page_size)
        ps <<= 1;

    if (fp->page_size != ps)
    {
        fp->page_size = ps;
        iofp_flush(fp);
        iofp_clear(fp);
    };

    // threshold.flush
    ps <<= 1;
    fp->flush_threshold = (otp->flush_threshold < ps ? ps : otp->flush_threshold) / fp->page_size;
};

#define iofp_load_page(fp, page) io_read_page(&(fp)->io, (page)->offset, (page)->buff, (fp)->page_size)
#define iofp_save_page(fp, page) io_write_page(&(fp)->io, (page)->offset, (page)->buff, (fp)->page_size)

void iofp_flush(struct iofp *const restrict fp)
{
    struct iofp_page *page = fp->anchor.next;
    do
    {
        if (page->changed)
        {
            iofp_save_page(fp, page);
            page->changed = false;
        };
    } while ((page = page->next)->offset >= 0);
};

void iofp_clear(struct iofp *const restrict fp)
{
    struct iofp_page *page = fp->anchor.next;
    while (page->buff)
        page_free((page = page->next)->prev);
    fp->count = 0;
};

void iofp_close(struct iofp *const restrict fp)
{
    iofp_flush(fp);
    iofp_clear(fp);
    io_close(&fp->io);
    free(fp);
};

void *iofp_locate(struct iofp *const restrict fp, const off_t offset, struct iofp_page **found_page)
{
    const off_t p_offset = offset % fp->page_size, page_offset = offset - p_offset;
    struct iofp_page *const restrict anchor = &fp->anchor;
    struct iofp_page *restrict page = anchor->next, *restrict a_page = NULL;
    if (page->offset != page_offset) // if not first page
    {
        register off_t o;
        while ((o = (page = page->next)->offset) != page_offset)
            if (o >= 0)
            {
                if (!page->changed)
                    a_page = page;
            }
            else
            {
                if (fp->count >= fp->flush_threshold)
                {
                    if (a_page)
                    {
                        page = a_page;
                    }
                    else
                    {
                        iofp_flush(fp);
                        page = anchor->prev;
                    };
                }
                else
                {
                    page = page_gen(fp);
                    ++fp->count;
                };

                page->offset = page_offset;
                iofp_load_page(fp, page);
                break;
            };

        (page->prev->next = page->next)->prev = page->prev;                       // detach
        (((page->next = anchor->next)->prev = page)->prev = anchor)->next = page; // move page to the first position
    };

    return (*found_page = page)->buff + p_offset;
};

off_t iofp_offsettoptr(struct iofp *const restrict fp, void *const restrict ptr, struct iofp_page **found_page)
{
    const size_t page_size = fp->page_size;
    struct iofp_page *page = &fp->anchor;
    size_t _p;
    void *buff;

    while ((buff = (page = page->next->buff)))
        if (ptr >= buff && (_p = ptr - buff) < page_size)
            return (*found_page = page)->offset + _p;

    *found_page = NULL;
    return -1;
};

void iofp_read(struct iofp *const restrict fp, off_t offset, void *restrict buffer, size_t nbyte)
{
    const off_t page_size = fp->page_size;
    struct iofp_page *page;
    void *ptr;
    off_t load;
    while (nbyte)
    {
        ptr = iofp_locate(fp, offset, &page);
        if ((load = page->buff + page_size - ptr) > nbyte)
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
        ptr = iofp_locate(fp, offset, &page);
        if ((load = page->buff + page_size - ptr) > nbyte)
            load = nbyte;
        page->changed = true;
        memcpy(ptr, buffer, load);
        offset += load;
        buffer += load;
        nbyte -= load;
    };
};

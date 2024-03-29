#define _GNU_SOURCE   // to use F_OFD_SETLKW
#include <errno.h>    // errno
#include <fcntl.h>    // F_OFD_SETLKW
#include <fcntl.h>    // open flags
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, aligned_alloc
#include <stdlib.h>   // exit
#include <string.h>   // strerror, memcpy
#include <sys/stat.h> // fstat, stat
#include <sys/uio.h>  // iovec, preadv
#include <unistd.h>   // open, sysconf
#include "pstream.h"

/* file page mapping */
#define pstream_buff_of_page(page) page->iovec.iov_base

static ssize_t page_load(struct pstream *const restrict ps, struct pstream_page *const restrict page)
{
    ssize_t bytes = preadv(ps->filedes, &page->iovec, 1, page->offset);
    if (bytes < 0)
    { // #TODO: error handling
        printf("\npreadv error: [%s]\n", strerror(errno));
        pstream_close(ps);
        exit(bytes);
    }
    else if ((bytes -= page->iovec.iov_len) > 0)
        memset(page->iovec.iov_base + bytes, 0, page->iovec.iov_len - bytes);

    page->changed = false;
    return bytes;
};

static ssize_t page_save(struct pstream *const restrict ps, struct pstream_page *const restrict page)
{
    ssize_t bytes = pwritev(ps->filedes, &page->iovec, 1, page->offset);
    if (bytes < 0)
    { // #TODO: error handling
        printf("\npwritev error: [%s]\n", strerror(errno));
        pstream_close(ps);
        exit(bytes);
    };

    page->changed = false;
    return bytes;
};

static struct pstream_page *load_page(struct pstream *const restrict ps, const off_t page_offset)
{
    struct pstream_page *page = malloc(sizeof(struct pstream_page));
    page->iovec.iov_len = ps->page_size;
    page->iovec.iov_base = aligned_alloc(page->iovec.iov_len, page->iovec.iov_len);
    page->offset = page_offset;
    page_load(ps, page);
    page->next = page->prev = NULL;
    return page;
};

static void free_page(struct pstream_page *const restrict page)
{
    free(page);
};

static struct pstream_page *page_of_offset(struct pstream *const restrict ps, const off_t offset, off_t *const restrict offset_p)
{
    off_t page_offset = offset - (*offset_p = offset % ps->page_size);
    struct pstream_page *page = ps->pages_head, *_p = NULL;

    while (page && page->offset != page_offset)
        page = (_p = page)->next;

    if (page)
    {
        if (page == ps->pages_head)
            return page;
    }
    else
    {
        ++ps->__page_count;
        while (_p && ps->__page_count >= ps->page_max)
        {
            if (!_p->changed)
            {
                if (_p->prev)
                {
                    _p->prev->next = _p->next;
                }
                else
                    ps->pages_head = _p->next;

                if (_p->next)
                    _p->next->prev = _p->prev;

                free_page(_p);
                --ps->__page_count;
            };
            _p = _p->prev;
        };
        page = load_page(ps, page_offset);
    };

    if (page->prev)
        page->prev->next = page->next;
    if (page->next)
        page->next->prev = page->prev;

    page->prev = NULL;
    if (page->next = ps->pages_head)
        page->next->prev = page;
    return ps->pages_head = page;
};

/* Paged stream */
struct pstream *pstream_open(const char *const restrict filename, const size_t poolsize)
{
    struct pstream *ps = malloc(sizeof(struct pstream));
    int fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd < 0) // #TODO: error handling
    {
        printf("fd error: [%s]\n", strerror(errno));
        close(fd);
        exit(-1);
    };

    ps->flock.l_whence = SEEK_SET;
    ps->flock.l_start = 0;
    ps->flock.l_len = 0;

    ps->filedes = fd;
    ps->pages_head = NULL;

    struct stat st;
    if (fstat(fd, &st)) // #TODO: error handling
    {
        printf("\nfstat error: [%s]\n", strerror(errno));
        close(fd);
        exit(-1);
    };

    off_t b = 512, bs = (off_t)st.st_blksize;
    while (b < bs)
        b <<= 1;
    ps->page_size = b;

    ps->page_max = (poolsize ? poolsize : st.st_size) / b;
    if (ps->page_max < 2)
        ps->page_max = 2;
    ps->__page_count = 0;

    return ps;
};

void pstream_lock(struct pstream *const restrict ps)
{
    ps->flock.l_type = F_WRLCK;
    fcntl(ps->filedes, F_SETLKW, &ps->flock);
};

void pstream_unlock(struct pstream *const restrict ps)
{
    ps->flock.l_type = F_UNLCK;
    fcntl(ps->filedes, F_SETLK, &ps->flock);
};

void pstream_read(struct pstream *const restrict ps, off_t offset, void *restrict buffer, size_t nbyte)
{
    off_t off_p, load, page_size = ps->page_size;
    do
    {
        struct pstream_page *page = page_of_offset(ps, offset, &off_p);
        load = page_size - off_p;
        if (load >= nbyte)
            load = nbyte;
        memcpy(buffer, pstream_buff_of_page(page) + off_p, load);
        nbyte -= load;
        offset += load;
        buffer += load;
    } while (nbyte);
};

void pstream_write(struct pstream *const restrict ps, off_t offset, const void *restrict buffer, size_t nbyte)
{
    off_t offset_p, load, page_size = ps->page_size;
    do
    {
        struct pstream_page *page = page_of_offset(ps, offset, &offset_p);
        page->changed = true;
        load = page_size - offset_p;
        if (load >= nbyte)
            load = nbyte;
        memcpy(pstream_buff_of_page(page) + offset_p, buffer, load);
        nbyte -= load;
        offset += load;
        buffer += load;
    } while (nbyte);
};

void pstream_flush(struct pstream *const restrict ps)
{
    struct pstream_page *page = ps->pages_head;
    while (page)
    {
        if (page->changed)
            page_save(ps, page);
        page = page->next;
    };
};

void pstream_clear(struct pstream *const restrict ps)
{
    struct pstream_page *page = ps->pages_head;
    ps->pages_head = NULL;
    while (page)
    {
        free_page(page);
        page = page->next;
    };
    ps->__page_count = 0;
};

void pstream_close(struct pstream *const restrict ps)
{
    pstream_clear(ps);
    close(ps->filedes);
    free(ps);
};

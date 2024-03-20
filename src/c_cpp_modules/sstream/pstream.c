#include <errno.h>    // errno
#include <fcntl.h>    // open flags
#include <stdio.h>    // printf
#include <stdlib.h>   // exit
#include <stdlib.h>   // aligned_alloc
#include <string.h>   // strerror, memcpy
#include <sys/stat.h> // fstat, stat
#include <sys/uio.h>  // iovec, preadv
#include <unistd.h>   // open, sysconf
#include "pstream.h"

/* file page mapping */
#define pstream_buff_of_page(page) page->iovec.iov_base

static ssize_t page_load(struct pstream *ps, struct pstream_page *page)
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

static ssize_t page_save(struct pstream *ps, struct pstream_page *page)
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

static struct pstream_page *load_page(struct pstream *ps, off_t page_offset)
{
    struct pstream_page *page = malloc(sizeof(struct pstream_page));
    page->iovec.iov_len = ps->page_size;
    page->iovec.iov_base = aligned_alloc(page->iovec.iov_len, page->iovec.iov_len);
    page->offset = page_offset;
    page_load(ps, page);
    page->next = page->prev = NULL;
    return page;
};

static void free_page(struct pstream_page *page)
{
    free(page);
};

/* Paged stream */
int pstream_open(struct pstream *ps, const char *filename, int page_max)
{
    int fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd < 0) // #TODO: error handling
    {
        printf("fd error: [%s]\n", strerror(errno));
        close(fd);
        exit(-1);
    };

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
    ps->page_max = page_max > 0 ? page_max : 32;
    ps->__page_count = 0;

    return 0;
};

static struct pstream_page *page_of_offset(struct pstream *ps, off_t offset, off_t *offset_p)
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
        if (++ps->__page_count >= ps->page_max)
        {
            if (_p)
            {
                if (_p->prev)
                {
                    _p->prev->next = NULL;
                }
                else
                    ps->pages_head = NULL;
                free_page(_p);
            };
            --ps->__page_count;
        };
        page = load_page(ps, page_offset);
    };

    if (page->prev)
    {
        page->prev->next = page->next;
        page->prev = NULL;
    };
    if (page->next)
        page->next->prev = page->prev;

    if (page->next = ps->pages_head)
        page->next->prev = page;

    return ps->pages_head = page;
};

ssize_t pstream_read(struct pstream *ps, off_t offset, void *buffer, size_t nbyte)
{
    off_t offset_p, load, page_size = ps->page_size;
    do
    {
        struct pstream_page *page = page_of_offset(ps, offset, &offset_p);
        load = page_size - offset_p;
        if (load >= nbyte)
            load = nbyte;
        memcpy(buffer, pstream_buff_of_page(page) + offset_p, load);
        nbyte -= load;
        offset += load;
        buffer += load;
    } while (nbyte);

    return nbyte;
};

ssize_t pstream_write(struct pstream *ps, off_t offset, const void *buffer, size_t nbyte)
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

    return nbyte;
};

int pstream_flush(struct pstream *ps)
{
    struct pstream_page *page = ps->pages_head;
    while (page)
    {
        if (page->changed)
            page_save(ps, page);
        page = page->next;
    };
    return 0;
};

int pstream_clear(struct pstream *ps)
{
    pstream_flush(ps);
    struct pstream_page *page = ps->pages_head;
    ps->pages_head = NULL;
    while (page)
    {
        free_page(page);
        page = page->next;
    };
    ps->__page_count = 0;
    return 0;
};

int pstream_close(struct pstream *ps)
{
    pstream_clear(ps);
    return close(ps->filedes);
};

int main()
{
    struct pstream ps;
    char *test = "0123456789012345678901234567890123456789";
    char buff[50];

    // #TODO: Locking?
    pstream_open(&ps, "./pstreamtest.db", 1);

    printf("\nREAD\n");
    pstream_read(&ps, 4090, buff, 10);
    buff[10] = 0;
    printf("Read :%s\n", buff);

    printf("\nWRITE\n");
    pstream_write(&ps, 4090, test, strlen(test));
    printf("Write : Done\n");

    pstream_close(&ps);
    return 0;
};

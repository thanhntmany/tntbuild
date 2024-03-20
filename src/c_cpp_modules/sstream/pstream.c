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
int pstream_open(struct pstream *ps, const char *filename)
{
    int fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    printf("\nfd: [%i]\n", fd);
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
    ps->__file_size = st.st_size;

    off_t b = 512, bs = (off_t)st.st_blksize;
    while (b < bs)
        b <<= 1;
    ps->page_size = b;

    return 0;
};

static struct pstream_page *page_of_offset(struct pstream *ps, off_t offset, off_t *offset_p)
{
    off_t page_offset = offset - (*offset_p = offset % ps->page_size);

    struct pstream_page *page = ps->pages_head;
    while (page)
    {
        if (page->offset == page_offset)
            return page;
        page = page->next;
    };

    page = load_page(ps, page_offset);
    page->next = ps->pages_head;
    ps->pages_head = page;
    return page;
};

ssize_t pstream_read(struct pstream *ps, off_t offset, void *buffer, size_t nbyte)
{
    off_t offset_p;
    struct pstream_page *page = page_of_offset(ps, offset, &offset_p);

    printf("offset_p :%ld\n", offset_p);
    printf("pstream_buff_of_page :%p\n", pstream_buff_of_page(page));
    printf("iov_base :%p\n", page->iovec.iov_base);
    printf("iov_len :%ld\n", page->iovec.iov_len);
    printf("offset_p :%ld\n", offset_p);
    printf("from :%p\n", pstream_buff_of_page(page) + offset_p);
    // printf("old :%s", test);

    memcpy(buffer, pstream_buff_of_page(page) + offset_p, nbyte);
    // #TODO: overflow to next pages
    return 0;
};

ssize_t pstream_write(struct pstream *ps, off_t offset, const void *buffer, size_t nbyte)
{
    off_t offset_p;
    struct pstream_page *page = page_of_offset(ps, offset, &offset_p);
    page->changed = true;
    // memcpy(((void *)pstream_buff_of_page(page)) + offset_p, buffer, nbyte);
    memcpy(pstream_buff_of_page(page) + offset_p, buffer, nbyte);
    // #TODO: overflow to next pages
    return 0;
};

int pstream_flush(struct pstream *ps)
{
    struct pstream_page *page = ps->pages_head;
    while (page)
    {
        if (page->changed)
        {
            page_save(ps, page);
            printf("Save page: %ld\n", page->offset);
        };
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
    return 0;
};

int pstream_close(struct pstream *ps)
{
    // #TODO:
    pstream_flush(ps);
    return close(ps->filedes);
};

int main()
{
    struct pstream ps;
    char *test = "ok somaethinga here okkkkkkkkke";
    char buff[50];

    // #TODO: Locking?
    pstream_open(&ps, "./pstreamtest.db");
    pstream_read(&ps, 5, buff, 6);
    buff[6] = 0;
    printf("old :%s\n", buff);

    // test = "newwww";
    pstream_write(&ps, 3, test, strlen(test));
    pstream_close(&ps);
    return 0;
};

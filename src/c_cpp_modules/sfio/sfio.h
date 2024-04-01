#ifndef SFIO_H
#define SFIO_H

#include <fcntl.h>     // struct flock
#include <stddef.h>    // size_t
#include <stdint.h>    // int8_t
#include <sys/types.h> // off_t
#include <sys/uio.h>   // struct iovec

/****************************************************
 *
 * SFIO file header metadata
 *
 */

// need be aligned to 2^n offset
struct __attribute__((packed)) sfio_segheader
{
    int64_t used;
    int64_t size;
};

#define SFILE_SIGNATURE "tnt/sfio:0.0.01"
/**
 * @member pagesize_l: the number of bits used for page size.
 *         pagesize (bytes) = 2^pagesize_l
 */
struct __attribute__((packed)) sfio_f_header
{
    char sfile_signature[sizeof(SFILE_SIGNATURE)];
    uint8_t pagesize_l; // 0->225: default: 12 -> 2^12 (B) = 4 (KB)
    int64_t next_offset;
    int64_t next_id;
};

/****************************************************
 *
 * In process env
 *
 */

struct sfio_page
{
    off_t offset;
    struct sfio_page *prev;
    struct sfio_page *next;
    struct iovec iovec; // --> ptr to page buffer
    bool changed;
};

struct sfio
{
    struct sfio_page *first_page;
    struct sfio_f_header *F;
    int filedes;
    struct flock flock;
};

/* Function */
// I/O
struct sfio *sfio_open();               // lock write (+read)
void sfio_flush(struct sfio *const sf); // write changed page into storage
void sfio_close(struct sfio *const sf); // flush + unlock write (+read)
void sfile_defrag(struct sfio *const sf);

// Page related
off_t sfio_offset_of_ptr(struct sfio *sf, void *ptr);
void *sfio_ptr_of_offset(struct sfio *sf, off_t offset);
void sfio_markchanged();

// segment
struct sfio_segheader *sfio_alloc(struct sfio *sf, size_t size);
void sfio_free(struct sfio *sf, struct sfio_segheader *sh);
#define sfio_buff_of_seg(sh_ptr) (sh_ptr + sizeof(sfio_segheader))

#endif

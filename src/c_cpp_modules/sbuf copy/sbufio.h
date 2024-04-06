#ifndef SBUFIO_H
#define SBUFIO_H

#include <fcntl.h>   // flock, off_t
#include <stdbool.h> // bool
#include <stdint.h>  // uint8_t, int64_t

/**************************************
 * segbuf
 */

struct __attribute__((packed)) sbuf_header
{
    off_t size; // `size` is always increased, never decreased.
    off_t used; // `used` always < `size`
    // char buffer[size]
};

struct sbuf
{
    struct sbuf_header h;
    void *buf;
    off_t id;
};

/**************************************
 * segbufIO
 */

/* sbufio_idx */

struct sbufio_idx_page
{
    off_t offset;
    struct sbufio_idx_page *next;
    struct sbufio_idx_page *prev;
    off_t *buf; // off_t *buf;
    bool changed;
    void *sbs; // struct sbuf **sbs;
    size_t nref;
};

/**
 * NOTE: id 0 is used for storing Lowest Available ID.
 */
struct __attribute__((packed)) sbufio_idx_id0
{
    off_t _tail_id; // Lowest Available ID
};

struct sbufio_idx
{
    struct sbufio_idx_page anchor_page;
    int fd;
    size_t _page_size;
    struct flock flock;
    struct sbufio_idx_id0 *i0;
};

/* sbufio_db */

struct sbufio_db_page
{
    off_t offset;
    struct sbufio_db_page *next;
    struct sbufio_db_page *prev;
    off_t *buf;
    // size_t nref;
    bool changed;
};

/* sbufio_db_sbuf */

/**
 * NOTE: First bytes in file is used for storing Lowest Available ID.
 */
struct __attribute__((packed)) sbufio_sb0
{
    struct sbuf_header h;
    char signature[10]; // #TODO:
    off_t next_offset;
};

struct sbufio_db
{
    struct sbufio_db_page anchor_page;
    int fd;
    size_t _page_size;
    struct flock flock;
    struct sbufio_sb0 *sb0;
};

/* sbufio */

struct sbufio
{
    struct sbufio_idx *idx;
    struct sbufio_db *db;
    /* data */
};

// struct sbuf *sbuf_alloc(const size_t size, const size_t ex);
// void sbuf_free(struct sbuf *sb);

// struct sbufio *sbufio_open(const char *const filename);
// void sbufio_close(struct sbufio *sbio);
// off_t sbufio_set(struct sbufio *const sbio, const off_t id, struct sbuf *const sb);
// struct sbuf *sbufio_get(struct sbufio *const sbio, const off_t id);

#endif
#ifndef SBUFIO_H
#define SBUFIO_H

#include <fcntl.h>   // flock
#include <stdbool.h> // bool
#include <stdint.h>  // uint8_t, int64_t
#include "sbuf/sbuf.h"

/**************************************
 * sbufio_idx
 */

/* idx File struct
 *
 * offset: value
 *      0: [last id -> N]
 *      1: [offset 1]
 *      2: [offset 2]
 *      3: [offset 3]
 *      3: [offset 3]
 *    ...: [offset 1]
 *     18: [       0]
 *    ...: [offset 1]
 *     20: [     -18]
 *    ...: [offset 1]
 *    ...: [offset 1]
 *      N: [neg id -> prev freed id. Eg: -20]
 *
 */

/**
 * @param nref: The number of references pointing in this page.
 * Page will be flushed automatically whenever nref were reduced to 0.
 */
struct sbufio_idx_page
{
    off_t offset;
    struct sbufio_idx_page *prev;
    struct sbufio_idx_page *next;
    void *buf; // off_t*
    void *sbs; // struct sbufio_seg **
    size_t nref;
    bool changed;
};

struct sbufio_idx
{
    struct sbufio_idx_page anchor_page; // .id = -1
    // lowest_available_id
    int fd;
    size_t _page_size;
    struct flock flock;
};

/**************************************
 * sbufio_db
 *
 * NOTE: In db file, offset 0 is used for file signature.
 * Thus, offet to 0 means NULL.
 */

/**
 * @param nref: The number of references pointing in this page.
 * Page will be flushed automatically whenever nref were reduced to 0.
 */
struct sbufio_db_page
{
    off_t offset;
    struct sbufio_db_page *prev;
    struct sbufio_db_page *next;
    off_t *buf;
    size_t nref;
};

struct sbufio_db
{
    struct sbufio_db_page anchor_page; // .offset = -1
    size_t _page_size;
    int fd;
    struct flock flock;
};

/**************************************
 * sbufio
 */

struct sbufio
{
    struct iofp *db;
    struct sbufio_idx *idx;
};

#endif
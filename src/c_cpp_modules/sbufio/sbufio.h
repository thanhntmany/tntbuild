#ifndef SBUFIO_H
#define SBUFIO_H

#include <fcntl.h>   // flock, off_t
#include <stdbool.h> // bool
#include <stdint.h>  // uint8_t, int64_t
#include "sbuf/sbuf.h"
#include "iofp/iofp.h"
#include "memp/memp.h"

/**************************************
 * sdb: segments management
 */

typedef off_t sbufio_sdb_offset;

struct sbufio_sdb
{
    struct iofp *fp;
    sbufio_sdb_offset tail;
    size_t sumoffree;
};

/**************************************
 * idx: indexing management
 */

typedef off_t sbufio_idx_id;

struct sbufio_idx
{
    struct iofp *fp;
    sbufio_idx_id la; // lowest available id
};

/**************************************
 * segbufIO
 */

#define SFILE_SIGNATURE "tnt/sbufio:0.0.1"
struct __attribute__((packed)) sbufio_metadata
{
    char signature[sizeof(SFILE_SIGNATURE)];
    sbufio_sdb_offset sdb_tail;
    size_t sdb_sumoffree;
    sbufio_idx_id idx_la;
};

typedef struct sbuf **sbufio_idm_value;

struct sbufio
{
    struct memp *idm;
    struct sbufio_idx idx;
    struct sbufio_sdb sdb;
    struct sbufio_metadata meta;
};

struct sbufio *sbufio_open(const char *const restrict filename);
void sbufio_flush(struct sbufio *const restrict sbio);
void sbufio_close(struct sbufio *const restrict sbio);

sbufio_idx_id sbufio_set(struct sbufio *const restrict sbio, sbufio_idx_id id, struct sbuf *const restrict new_sb);
struct sbuf *sbufio_get(struct sbufio *const restrict sbio, const sbufio_idx_id id);

#endif
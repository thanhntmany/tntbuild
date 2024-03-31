#ifndef IOFPB_H
#define IOFPB_H

#include <stdint.h>
#include "iofp/iofp.h"

#define IOFPB_SIGNATURE "tnt/iofpb"
#define IOFPB_VERSION \
    {                 \
        .major = 0,   \
        .minor = 0,   \
        .patch = 1    \
    }

#define IOFPB_IDXFILESUFFIX ".idx"

typedef off_t iofpb_id;

struct __attribute__((packed)) iofpb_fblockh
{
    size_t used;
    size_t size;
};
#define iofpb_buffoffbh(bh) (void *)((void *)bh + sizeof(struct iofpb_fblockh))
#define iofpb_markchanged(fpb, ptr) iofp_markchanged(fpb->fp, ptr)

struct iofpb_blockh
{
    struct iofpb_fblockh *f;
    struct iofp_page *page;
    iofpb_id id;
    off_t offset;
};
#define iofpb_buffoblockh(bh) (void *)((void *)bh->f + sizeof(struct iofpb_fblockh))

struct __attribute__((packed)) iofpb_fversion
{
    int32_t major;
    int32_t minor;
    int32_t patch;
};

struct __attribute__((packed)) iofpb_fheader
{
    char _signature[sizeof(IOFPB_SIGNATURE)];
    struct iofpb_fversion _version;
    off_t next_offset;
    iofpb_id next_id;
    uint8_t page_size_bits; // page_size = 2^page_size_bits (Bytes)
    // first segment
};

struct iofpb
{
    struct iofpb_fheader *f;
    struct iofp_page *f_page;
    struct iofp *fpi;
    struct iofp *fp;
    size_t page_size;
};

struct iofpb *iofpb_open(const char *const restrict filename);
void *iofpb_alloc(struct iofpb *const restrict fpb, const size_t size, struct iofpb_blockh *const restrict bh);
void iofpb_free(struct iofpb_blockh *const restrict bh);
void iofpb_close(struct iofpb *const restrict fps);

#endif

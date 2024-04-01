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

struct __attribute__((packed)) iofpb_fblockh
{
    size_t used;
    size_t size;
    // buffer
};
#define iofpb_buffofblock(bh) (void *)((void *)(bh) + sizeof(struct iofpb_fblockh))
#define iofpb_markchanged(fpb, ptr) iofp_markchanged(fpb->fp, ptr)

struct iofpb_blockh
{
    struct iofpb_fblockh *f;
    struct iofp_page *page;
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
    uint8_t page_size_bits; // page_size = 2^page_size_bits (Bytes)
    // first segment
};

struct iofpb
{
    struct iofpb_fheader *f;
    struct iofp_page *f_page; // fist page, where the iofpb_fheader are placed
    struct iofp *fp;
    size_t page_size;
};

struct iofpb *iofpb_open(const char *const restrict filename);
void *iofpb_alloc(struct iofpb *const restrict fpb, const size_t size, struct iofpb_blockh *const restrict bh);
void *iofpb_get(struct iofpb *const restrict fpb, const off_t offset, struct iofpb_blockh *const restrict bh);
void iofpb_free(struct iofpb_blockh *const restrict bh);
void iofpb_close(struct iofpb *const restrict fps);

#endif

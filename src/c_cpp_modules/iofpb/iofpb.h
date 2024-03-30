#ifndef IOFPB_H
#define IOFPB_H

#include <stdint.h>
#include "iofp/iofp.h"

#define IOFPB_SIGNATURE "tnt/iofpb"
#define IOFPB_VERSION                      \
    {                                      \
        .major = 9, .minor = 9, .patch = 9 \
    }

struct __attribute__((packed)) iofpb_fblockh
{
    size_t used;
    size_t size;
};
#define iofpb_buffofblock(bh) (void *)((void *)bh + sizeof(struct iofpb_fblockh))
#define iofpb_markchanged(fpb, ptr) iofp_markchanged(fpb->fp, ptr)

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
    struct iofp_page *f_page;
    struct iofp *fp;
    size_t page_size;
};

struct iofpb *iofpb_open(const char *const restrict filename);
struct iofpb_fblockh *iofpb_alloc(struct iofpb *const restrict fps, const size_t size);
void iofpb_free(struct iofpb *const restrict fps, struct iofpb_fblockh *const restrict sh);
void iofpb_close(struct iofpb *const restrict fps);

#endif

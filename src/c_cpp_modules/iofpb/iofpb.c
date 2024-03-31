#include <stdlib.h>  // malloc, alloca
#include <stdbool.h> // bool
#include <string.h>  // memcmp, memcpy
#include "iofpb/iofpb.h"

#include <stdio.h>

static const char _iofps_signature[] = IOFPB_SIGNATURE;
static const struct iofpb_fversion _iofps_version = IOFPB_VERSION;
static const char _iofps_idxfilesuffix[] = IOFPB_IDXFILESUFFIX;

struct iofpb *iofpb_open(const char *const restrict filename)
{
    size_t filename_len = strlen(filename);
    char *const restrict filename_index = alloca(filename_len + sizeof(_iofps_idxfilesuffix));
    memcpy(filename_index, filename, filename_len);
    memcpy(filename_index + filename_len, _iofps_idxfilesuffix, sizeof(_iofps_idxfilesuffix));

    struct iofpb *const restrict fpb = malloc(sizeof(struct iofpb));
    fpb->fpi = iofp_open(filename_index);
    fpb->fp = iofp_open(filename);

    struct iofp_page *page;
    struct iofpb_fheader *f = fpb->f = iofp_ptrtooffset(fpb->fp, 0, &page);
    fpb->f_page = page;

    if (memcmp(f->_signature, _iofps_signature, sizeof(_iofps_signature)))
    {
        memcpy(f->_signature, _iofps_signature, sizeof(_iofps_signature));
        memcpy(&f->_version, &_iofps_version, sizeof(_iofps_version));
        f->next_offset = sizeof(struct iofpb_fheader);
        f->next_id = 0;

        size_t ps = fpb->fp->page_size;
        uint8_t b = 1;
        while (ps >>= 1)
            ++b;
        f->page_size_bits = --b;
        iofp_markpagechanged(page);
    };

    fpb->page_size = 1 << f->page_size_bits;
    iofp_markpagechanged(page);

    struct iofp_opt opt = {.page_size = fpb->page_size, .keep = 0, .flush = 0};
    iofp_setotp(fpb->fp, &opt);

    return fpb;
};

#define set_id_value(fpi, page, id, value)                                 \
    *(off_t *)iofp_ptrtooffset(fpi, (id) * sizeof(iofpb_id), &(page)) = value; \
    iofp_markpagechanged(page);

void *iofpb_alloc(struct iofpb *const restrict fpb, const size_t size, struct iofpb_blockh *const restrict bh)
{
    const size_t req = size + sizeof(struct iofpb_fblockh), page_size = fpb->fp->page_size;
    if (req > page_size)
        return NULL;

    struct iofp_page *page;

    off_t offset = fpb->f->next_offset;
    const size_t page_availib = page_size - (offset % page_size);

    struct iofpb_fblockh *fbh = iofp_ptrtooffset(fpb->fp, offset, &page);
    if (page_availib < req + sizeof(struct iofpb_fblockh))
    {
        fbh->used = 0;
        fbh->size = page_availib;
        iofp_markpagechanged(page);
        offset += page_availib;
        fbh = iofp_ptrtooffset(fpb->fp, offset, &page);
    };

    bh->f = fbh;
    fbh->used = fbh->size = req;
    bh->page = page;
    iofp_markpagechanged(page);

    set_id_value(fpb->fpi, page, bh->id = fpb->f->next_id, bh->offset = offset);

    fpb->f->next_id++;
    fpb->f->next_offset = offset + req;
    iofp_markpagechanged(fpb->f_page);
    return iofpb_buffoffbh(fbh);
};

void iofpb_free(struct iofpb_blockh *const restrict bh)
{
    bh->f->used = 0;
    iofp_markpagechanged(bh->page);
};

void iofpb_close(struct iofpb *const restrict fpb)
{
    iofp_close(fpb->fp);
    iofp_close(fpb->fpi);
    free(fpb);
};
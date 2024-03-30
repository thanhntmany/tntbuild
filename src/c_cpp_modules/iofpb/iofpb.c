#include <stdlib.h>  // malloc
#include <stdbool.h> // bool
#include <string.h>  // memcmp, memcpy
#include "iofpb/iofpb.h"

static const char _iofps_signature[] = IOFPB_SIGNATURE;
static const struct iofpb_fversion _iofps_version = IOFPB_VERSION;

struct iofpb *iofpb_open(const char *const restrict filename)
{
    struct iofpb *const restrict fpb = malloc(sizeof(struct iofpb));
    fpb->fp = iofp_open(filename);

    struct iofp_page *page;
    struct iofpb_fheader *f = fpb->f = iofp_ptrtooffset(fpb->fp, 0, &page);
    fpb->f_page = page;

    if (memcmp(f->_signature, _iofps_signature, sizeof(_iofps_signature)))
    {
        memcpy(f->_signature, _iofps_signature, sizeof(_iofps_signature));
        memcpy(&f->_version, &_iofps_version, sizeof(_iofps_version));
        f->next_offset = sizeof(struct iofpb_fheader);

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

struct iofpb_fblockh *iofpb_alloc(struct iofpb *const restrict fpb, const size_t size)
{
    size_t req = size + sizeof(struct iofpb_fblockh),
           page_size = fpb->fp->page_size;
    if (req > page_size)
        return NULL;

    off_t offset = fpb->f->next_offset;
    const size_t page_availib = page_size - (offset % page_size);

    struct iofp_page *page;
    struct iofpb_fblockh *bh = iofp_ptrtooffset(fpb->fp, offset, &page);

    if (page_availib < req + sizeof(struct iofpb_fblockh))
    {
        bh->used = 'X';
        bh->size = page_availib;
        iofp_markpagechanged(page);

        offset += page_availib;
        bh = iofp_ptrtooffset(fpb->fp, offset, &page);
    };

    fpb->f->next_offset = offset + (bh->used = bh->size = req);
    iofp_markpagechanged(page);
    iofp_markpagechanged(fpb->f_page);

    return bh;
};

void iofpb_free(struct iofpb *const restrict fpb, struct iofpb_fblockh *const restrict bh)
{
    struct iofp_page *page;
    if (iofp_offsettoptr(fpb->fp, bh, &page) < 0)
        return;
    bh->used = 0;
    iofp_markpagechanged(page);
};

// void iofpb_defrag(struct iofpb *const restrict fpb){
//     // #TODO:
// };

void iofpb_close(struct iofpb *const restrict fpb)
{
    iofp_close(fpb->fp);
    free(fpb);
};
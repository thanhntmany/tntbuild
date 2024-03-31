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

void *iofpb_alloc(struct iofpb *const restrict fpb, const size_t size, struct iofpb_blockh *const restrict bh)
{
    size_t req = size + sizeof(struct iofpb_fblockh),
           page_size = fpb->fp->page_size;
    if (req > page_size)
        return NULL;

    off_t offset = fpb->f->next_offset;
    const size_t page_availib = page_size - (offset % page_size);

    struct iofp_page *page;
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
    fpb->f->next_offset = (bh->offset = offset) + (fbh->used = fbh->size = req);
    bh->page = page;
    iofp_markpagechanged(page);
    iofp_markpagechanged(fpb->f_page);

    return (void *)fbh + sizeof(struct iofpb_fblockh);
};

void iofpb_free(struct iofpb_blockh *const restrict bh)
{
    bh->f->used = 0;
    iofp_markpagechanged(bh->page);
};

// void iofpb_defrag(struct iofpb *const restrict fpb){
//     // #TODO:
// };

void iofpb_close(struct iofpb *const restrict fpb)
{
    iofp_close(fpb->fp);
    free(fpb);
};
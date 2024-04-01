#include <stdlib.h> // free
#include "radixtree/radixtree.h"

static struct radixtree_walker *walker_init(struct sfile *const restrict sf)
{
    struct radixtree_walker *restrict wk = malloc(sizeof(struct radixtree_walker));
    wk->sf = sf;
    return wk;
};

static walker_free(struct radixtree_walker *const restrict wk)
{
    free(wk);
};


void radixtree_path2node(char *path){};
void radixtree_node2path(){};
void radixtree_list(char *path){};

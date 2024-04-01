#ifndef TNT_DB_PTREE_H
#define TNT_DB_PTREE_H

#include "sfile/sfile.h"

/*
 * Use prefix tree struct to treat paths segment.
 *
 *   file_path
 *      ↑│
 * [ prefix-tree ]
 *      │↓
 * PTreeNode { file_node = &FileNode; ... }
 *      ⤪
 * FileNode { ptree_node = &PTreeNode; ... }
 *
 */

/*
 * NOTE: Path segment bounding by *path and p_len (instead of Null-terminated).
 *
 * [ROOT]
 *   │
 * ══╪════════════════════════
 *   ├─*parent
 *   │  ├─*pre
 *   │  ├─[value] path segment
 *   │  │  └─ *child (first child)
 *   │  ├─*next
 *   V  V
 * ═══════════════════════════
 * E.g:
 *
 * [ROOT]
 *   ├─( )pro
 *   │  ├─( )duct     // product
 *   │  │  └─( )i
 *   │  │     ├─( )on // production
 *   │  │     └─( )ve // productive
 *   │  ├─( )files    // profiles
 *   │  └─( )perly    // properly
 *   ├─( )te
 *   │  ├─( )a        // tea
 *   │  │  ├─( )ch    // teach
 *   │  │  └─( )se    // tease
 *   │  ├─( )eth      // teeth
 *   │  └─( )sts      // tests
 *   │
 */

struct __attribute__((packed)) radixtree_node
{
    sfile_id parent;
    sfile_id first_child;
    sfile_id prev;
    sfile_id next;
    sfile_id value;
    char token[3 * sizeof(sfile_id)];
};

struct radixtree_walker
{
    struct sfile *sf;
    radixtree_node current;
};

#endif
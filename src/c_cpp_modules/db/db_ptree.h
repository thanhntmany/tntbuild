#ifndef TNT_DB_PTREE_H
#define TNT_DB_PTREE_H

#include <stdio.h>;
#include <stddef.h>;
#include <stdint.h>;

/*
 * SFile: Segmented file
 */

/*
 * .idb : mapping id to segment Declaration
 * .db  : store continuous segment
 */

/* id = offset of Segments Declaration in idb file (index maping) */
typedef struct
{
    int8_t id1; // 2^8 * sizeof(size_t) = 1KB || 2KB
    int8_t id2; // 2^8 * sizeof(size_t) = 1KB || 2KB
    int8_t id3; // 2^8 * sizeof(size_t) = 1KB || 2KB
    int8_t id4; // 2^8 * sizeof(size_t) = 1KB || 2KB
} DB_Key;

typedef union
{
    int32_t id;
    DB_Key key;
} DB_Key_U;

// DB_SegDec *segdec_offset = l1[dbkey.key.id1][dbkey.key.id2][dbkey.key.id3][dbkey.key.id4]

typedef struct
{
    size_t offset; // offset in .db file
    size_t size;
} DB_SegDec;

typedef struct
{
    DB_SegDec pagemap[65536];
    DB_Key nextKey;
    size_t nextOffset;
} DB_FileHeader;

typedef struct
{
    FILE *db;
    FILE *idb;
    
} DBHandler;

/*

key: 0 -> 2^32-1
2 B -> page : (2^16)*size_t = 512KB || 1024KB
2 B -> segm : (2^16)*size_t = 512KB || 1024KB
    size_t pageOffset = sf->mem->pageIdxSec[key->pageId];

offset = sf->file->pageIdxSec[key->pageId]

*/

typedef size_t TntDbFptreeNodeValue;      // *TntDbFptreeNodeInDB
typedef size_t TntDbFptreeNodeOffsetInDB; // *TntDbFptreeNodeInDB

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
typedef struct
{
    size_t parent;              // *TntDbFptreeNode
    size_t pre;                 // *TntDbFptreeNode
    size_t next;                // *TntDbFptreeNode
    size_t child;               // *TntDbFptreeNode
    size_t path;                // *char
    size_t p_len;               // len of char
    TntDbFptreeNodeValue value; // value of current node
} TntDbFptreeNodeInDB;

typedef struct
{
    TntDbFptreeNodeInDB db;
    size_t parent;              // *TntDbFptreeNode
    size_t pre;                 // *TntDbFptreeNode
    size_t next;                // *TntDbFptreeNode
    size_t child;               // *TntDbFptreeNode
    size_t path;                // *char
    size_t p_len;               // len of char
    TntDbFptreeNodeValue value; // value of current node
} TntDbFptreeNode;

#endif
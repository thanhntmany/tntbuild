#ifndef TNT_DB_H
#define TNT_DB_H

#include <time.h>

typedef struct
{
    char *path;
    char *build_script;
    char *onchange_script;
    char **dep;
    char **rel;
    char *dep_cache;
    char **rel_cache;
    char *src_definition;

    time_t ttime; // last tracked time
    time_t st_mtime; // Time of last data modification
    bool exists;
} TntTrackedFile;

#endif
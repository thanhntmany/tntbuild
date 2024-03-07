#ifndef TNT_DB_H
#define TNT_DB_H

#include <time.h>

typedef struct
{
    char *path;
    char *onchange_script;
    char **dependencies;
    char *build_script;
    char **companions;
    time_t utime; // last update time
    bool exists;
} TntTrackedFile;

#endif
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "app.h"

void app_exit_error(char *strerror)
{
    fprintf(stderr, "ERROR: %s\n", strerror);
    exit(-1);
};

char *tnt_getcwd()
{
    char *buf = NULL;
    char *ptr = NULL;
    size_t size = 256;

    do
    {
        if ((buf = realloc(buf, size)) == NULL)
            app_exit_error("tnt_getcwd, cwd: Cannot allocate enough memory.");

        ptr = getcwd(buf, size);

        if (ptr == NULL && errno != ERANGE)
            app_exit_error(strcat("tnt_getcwd, getcwd", strerror(errno)));
        size *= 2;

    } while (ptr == NULL);

    return ptr;
};

void app_select_dst(TntApp app)
{
    printf("app_select_dst\n");
};

void app_dep_add(TntApp app)
{
    printf("app_dep_add\n");
};

void app_dep_rm(TntApp app)
{
    printf("app_dep_rm\n");
};

void app_rel_add(TntApp app)
{
    printf("app_rel_add\n");
};

void app_rel_rm(TntApp app)
{
    printf("app_rel_rm\n");
};

void app_set_build_script(TntApp app)
{
    printf("app_set_build_script\n");
};

void app_set_onchange_script(TntApp app)
{
    printf("app_set_onchange_script\n");
};

void app_chdir(TntApp app)
{
    printf("app_chdir\n");
};

void app_get_tar(TntApp app)
{
    printf("app_get_tar\n");
};

void app_get_dep(TntApp app)
{
    printf("app_get_dep\n");
};

void app_get_rel(TntApp app)
{
    printf("app_get_rel\n");
};

void app_get_build_script(TntApp app)
{
    printf("app_get_build_script\n");
};

void app_get_onchange_script(TntApp app)
{
    printf("app_get_onchange_script\n");
};

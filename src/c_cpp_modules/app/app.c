#include <errno.h>
#include <stdio.h>
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

void app_select_target(TntApp app)
{
    printf("app_select_target");
};

void app_dep_add(TntApp app)
{
    printf("app_dep_add");
};

void app_dep_rm(TntApp app)
{
    printf("app_dep_rm");
};

void app_rel_add(TntApp app)
{
    printf("app_rel_add");
};

void app_rel_rm(TntApp app)
{
    printf("app_rel_rm");
};

void app_set_build_script(TntApp app)
{
    printf("app_set_build_script");
};

void app_set_onchange_script(TntApp app)
{
    printf("app_set_onchange_script");
};

void app_chdir(TntApp app)
{
    printf("app_chdir");
};

void app_get_tar(TntApp app)
{
    printf("app_get_tar");
};

void app_get_dep(TntApp app)
{
    printf("app_get_dep");
};

void app_get_rel(TntApp app)
{
    printf("app_get_rel");
};

void app_get_build_script(TntApp app)
{
    printf("app_get_build_script");
};

void app_get_onchange_script(TntApp app)
{
    printf("app_get_onchange_script");
};

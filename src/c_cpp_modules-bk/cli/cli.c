#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "app/app.h"
#include "cli.h"

static void exit_error(char *strerror)
{
    fprintf(stderr, "ERROR: %s\n", strerror);
    exit(-1);
};

static void cmd_select_dst(TntApp app, char ***argvPtr)
{
    char *token = *(++(*argvPtr));
    if (token)
    {
        if (!strcmp(token, "--"))
            token = NULL;
    }
    else
        --(*argvPtr);

    app_select_dst(app, token);
    printf("Select destination: %s\n", token);
};

static void cmd_dep_add(TntApp app, char ***argvPtr)
{
    app_dep_add(app);
    char *token;
    while (token = *(++(*argvPtr)))
    {
        if (!strcmp(token, "--"))
            return;
        printf("--> %s\n", token);
    };
    --(*argvPtr);
};

int main(int argc, char **argv)
{
    TntApp app;
    char *cmd = NULL;

    char *token;
    while (token = *(++argv))
    {
        printf("@Token: %s\n", token);

        if (!strcmp(token, "dst"))
        {
            cmd_select_dst(app, &argv);
            continue;
        };
        if (!strcmp(token, "dep"))
        {
            cmd_dep_add(app, &argv);
            continue;
        };
        if (!strcmp(token, "de-"))
        {
            cmd = "dep-";
            continue;
        };
        if (!strcmp(token, "rel"))
        {
            cmd = "rel";
            continue;
        };
        if (!strcmp(token, "re-"))
        {
            cmd = "rel-";
            continue;
        };
        if (!strcmp(token, "build-script"))
        {
            cmd = "build-script";
            continue;
        };
        if (!strcmp(token, "onchange-script"))
        {
            cmd = "onchange-script";
            continue;
        };
        if (!strcmp(token, "cd"))
        {
            cmd = "cd";
            continue;
        };
        if (!strcmp(token, "status"))
        {
            cmd = "status";
            continue;
        };

        if (!strcmp(token, "status"))
        {
            cmd = "status";
            break;
        };

        if (!strcmp(token, "--version"))
        {
            cmd = "version";
            break;
        };

        if (!strcmp(token, "--help"))
        {
            cmd = "help";
            break;
        };

        printf("Invalid argument \"%s\"\n", token);
        if (token)
        {
            printf("- Rest argument(s): ");
            do
            {
                printf("%s ", token);
            } while (token = *(++argv));
            printf("\n");
        };
        break;
    };

    if (!cmd)
        cmd = CMD_HELP;

    printf("@Run cmd %s\n", cmd);
    printf("%s", "\u2554");
    printf("\n");

    return 0;
};

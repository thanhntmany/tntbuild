#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "cli.h"

int main(int argc, char **argv)
{
    char *cmd = NULL;

    char *token;
    while (token = *(++argv))
    {
        printf("@Token %s\n", token);

        if (!strcmp(token, "tar"))
        {
            cmd = "tar";
            continue;
        };
        if (!strcmp(token, "dep") || !strcmp(token, "dep+"))
        {
            cmd = "dep";
            continue;
        };
        if (!strcmp(token, "dep-"))
        {
            cmd = "dep-";
            continue;
        };
        if (!strcmp(token, "rel") || !strcmp(token, "rel+"))
        {
            cmd = "rel";
            continue;
        };
        if (!strcmp(token, "rel-"))
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
    };

    if (!cmd)
        cmd = CMD_HELP;

    printf("@Run cmd %s\n", cmd);

    return 0;
};

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "cli.h"

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

int tnt_app_main_cmd(TntApp app, int argc, char **argv)
{

    char *cmd = NULL;
    char tmp_chr;
    app.cwd = tnt_getcwd();
    printf("Current working dir: %s\n", app.cwd);
    printf("sss %ld\n", CMD_LONGOTP_WORKINGDIRECTORY_LEN);

    // parse options
    char *token = NULL;
    while (token = *(++argv))
    {
        if (token[0] != '-')
        {
            --argv;
            break;
        };
        ++token;

        if (token[0] == '-')
        {
            ++token;
            // parse long options (starts with "--")
            if (!strcmp(token, "version"))
            {
                cmd = CMD_VERSION;
                goto run_cmd;
            };

            if (!strcmp(token, "help"))
            {
                cmd = CMD_HELP;
                goto run_cmd;
            };

            if (!strncmp(token, CMD_LONGOTP_WORKINGDIRECTORY, CMD_LONGOTP_WORKINGDIRECTORY_LEN))
            {
                cmd = CMD_HELP;
                goto run_cmd;
            };
        }
        else
        {
            tmp_chr = *token;
            if (tmp_chr == 'v')
            {
                cmd = CMD_VERSION;
                goto run_cmd;
            };

            if (*token == 'h')
            {
                cmd = CMD_HELP;
                goto run_cmd;
            };

            if (*token == 'd')
            {
                token = *(++argv);
                printf("@Set working directory: %s\n", token);
            };
        };
    };

    // parse command
    while (token = *(++argv))
    {
        if (!strcmp(token, "help"))
        {
            cmd = CMD_HELP;
            goto run_cmd;
        };
    };

    if (!cmd)
        cmd = CMD_HELP;
run_cmd:
    printf("@Run cmd %s\n", cmd);

    return 0;
};

int main(int argc, char **argv)
{
    TntApp App;
    return tnt_app_main_cmd(App, argc, argv);
};

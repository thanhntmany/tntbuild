#ifndef TNT_APP_H
#define TNT_APP_H

typedef struct
{
    char *cwd;
} TntApp;

void tnt_app_exit_error(char *strerror);
char *tnt_getcwd();
int tnt_app_main_cmd(TntApp app, int argc, char **argv);

#define CMD_LONGOTP_WORKINGDIRECTORY "working-directory="
#define CMD_LONGOTP_WORKINGDIRECTORY_LEN sizeof(CMD_LONGOTP_WORKINGDIRECTORY) - 1

#define CMD_VERSION "CMD_VERSION"
#define CMD_HELP "CMD_HELP"
#define CMD_LOAD "CMD_LOAD"
#define CMD_LIST "CMD_LIST"
#define CMD_STAT "CMD_STAT"
#define CMD_GRAPH "CMD_GRAPH"
#define CMD_MAKE "CMD_MAKE"

#endif
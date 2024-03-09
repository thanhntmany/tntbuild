void tnt_app_exit_error(char *strerror);
char *tnt_getcwd();

typedef struct
{
    char *cwd;
} TntApp;

void app_select_target(TntApp app);
void app_dep_add(TntApp app);
void app_dep_rm(TntApp app);
void app_rel_add(TntApp app);
void app_rel_rm(TntApp app);
void app_set_build_script(TntApp app);
void app_set_onchange_script(TntApp app);
void app_chdir(TntApp app);
void app_get_tar(TntApp app);
void app_get_dep(TntApp app);
void app_get_rel(TntApp app);
void app_get_build_script(TntApp app);
void app_get_onchange_script(TntApp app);

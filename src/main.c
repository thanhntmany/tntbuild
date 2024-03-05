#include <stdio.h>
#include <string.h>
#include "app.h"

int main(int argc, char **argv)
{
    TntApp App;
    return tnt_app_main_cmd(App, argc, argv);
};

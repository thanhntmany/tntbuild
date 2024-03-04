#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void tnt_exit_error(char *strerror)
{
    fprintf(stderr, "ERROR: %s\n", strerror);
    exit(-1);
};

char *tnt_getcwd()
{
    char *buf = NULL;
    char *ptr = NULL;
    size_t size = 512;

    do
    {
        if ((buf = realloc(buf, size)) == NULL)
            tnt_exit_error("tnt_getcwd, cwd: Cannot allocate memory.");

        ptr = getcwd(buf, size);

        if (ptr == NULL && errno != ERANGE)
            tnt_exit_error(strcat("tnt_getcwd, getcwd", strerror(errno)));
        size *= 2;

    } while (ptr == NULL);

    return ptr;
};

int main(int argc, char *argv[])
{
    printf("Current working dir: [%s]\n", tnt_getcwd());
    return 0;
};

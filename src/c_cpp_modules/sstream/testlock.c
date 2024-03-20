#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#define FILENAME "./testlock.txt"
#define NUM_THREADS 3
#define ITERATIONS 5

void *
thread_start(void *arg)
{
    int i, fd, len;
    long tid = (long)arg;
    char buf[256];
    struct flock lck = {
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 1,
    };

    fd = open(FILENAME, O_RDWR | O_CREAT, 0666);

    for (i = 0; i < ITERATIONS; i++)
    {
        lck.l_type = F_WRLCK;

        printf("@@ tid:%ld require lock.\n", tid);
        fcntl(fd, F_OFD_SETLKW, &lck);
        printf("@@ tid:%ld Run with lock.\n", tid);

        len = sprintf(buf, "%d: tid=%ld fd=%d jhfsadfjlajmef;ldsnfp;jkqdknvfjksandfkj\n", i, tid, fd);

        lseek(fd, 0, SEEK_END);
        write(fd, buf, len);
        fsync(fd);

        lck.l_type = F_UNLCK;
        printf("@@ tid:%ld Release lock.\n", tid);
        fcntl(fd, F_OFD_SETLK, &lck);

        /* sleep to ensure lock is yielded to another thread */
        usleep(1);
    }
    pthread_exit(NULL);
};

int main(int argc, char **argv)
{
    long i;
    pthread_t threads[NUM_THREADS];

    truncate(FILENAME, 0);

    for (i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, thread_start, (void *)i);

    pthread_exit(NULL);
    return 0;
};
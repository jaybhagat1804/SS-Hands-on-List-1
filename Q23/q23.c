#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>

int main()
{
    long max_files;
    int fd[2];
    int pipe_size;

    max_files = sysconf(_SC_OPEN_MAX);

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pipe_size = fcntl(fd[0], F_GETPIPE_SZ);

    if (pipe_size == -1)
    {
        perror("fcntl");
    }
    else
    {
        printf("Pipe size: %d bytes\n", pipe_size);
    }

    printf("Maximum open files: %ld\n", max_files);

    close(fd[0]);
    close(fd[1]);

    return 0;
}

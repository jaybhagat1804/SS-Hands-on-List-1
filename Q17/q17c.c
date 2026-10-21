#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int fd[2];

    pipe(fd);

    if (fork() == 0)
    {
        close(fd[0]);

        close(STDOUT_FILENO);
        fcntl(fd[1], F_DUPFD, STDOUT_FILENO);

        close(fd[1]);

        execlp("ls", "ls", "-l", NULL);
    }

    if (fork() == 0)
    {
        close(fd[1]);

        close(STDIN_FILENO);
        fcntl(fd[0], F_DUPFD, STDIN_FILENO);

        close(fd[0]);

        execlp("wc", "wc", NULL);
    }

    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}

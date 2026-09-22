#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int hour, minute;
    time_t now, target;
    struct tm *t;

    if (argc != 3)
    {
        printf("Usage: %s <HH> <MM>\n", argv[0]);
        return 1;
    }

    hour = atoi(argv[1]);
    minute = atoi(argv[2]);

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        printf("Daemon started with PID %d\n", pid);
        return 0;
    }

    setsid();

    chdir("/");

    umask(0);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1)
    {
        now = time(NULL);
        t = localtime(&now);

        if (t->tm_hour == hour && t->tm_min == minute)
        {
            system("/home/jay-bhagat/Desktop/home/SS/test.sh");
            break;
        }

        sleep(20);
    }

    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        sleep(2);

        printf("Child killing parent...\n");

        kill(getppid(), SIGKILL);
    }
    else
    {
        printf("Parent PID = %d\n", getpid());

        while (1)
        {
            printf("Parent running...\n");
            sleep(1);
        }
    }

    return 0;
}

#include <stdio.h>
#include <unistd.h>
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
        sleep(5);

        printf("Child PID = %d\n", getpid());
        printf("New Parent PID = %d\n", getppid());

        sleep(10);
    }
    else
    {
        printf("Parent exiting...\n");
        exit(0);
    }

    return 0;
}

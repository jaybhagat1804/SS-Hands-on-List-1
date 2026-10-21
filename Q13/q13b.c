#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int pid;

    if (argc != 2)
    {
        printf("Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid = atoi(argv[1]);

    kill(pid, SIGSTOP);

    printf("SIGSTOP sent\n");

    return 0;
}

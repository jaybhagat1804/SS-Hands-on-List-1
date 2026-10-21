#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("SIGALRM caught\n");
}

int main()
{
    signal(SIGALRM, handler);

    alarm(5);

    while (1)
        pause();

    return 0;
}

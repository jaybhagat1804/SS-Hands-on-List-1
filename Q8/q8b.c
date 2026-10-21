#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("\nSIGINT caught\n");
}

int main()
{
    signal(SIGINT, handler);

    printf("Press Ctrl+C\n");

    while (1)
        pause();

    return 0;
}

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig)
{
    if (sig == SIGSEGV)
        printf("SIGSEGV caught\n");

    else if (sig == SIGINT)
        printf("SIGINT caught\n");

    else if (sig == SIGFPE)
        printf("SIGFPE caught\n");
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGFPE, &sa, NULL);

    printf("Press Ctrl+C to test SIGINT\n");

    while (1)
        pause();

    return 0;
}

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void handler(int sig)
{
    printf("SIGPROF caught\n");
}

int main()
{
    struct itimerval timer;

    signal(SIGPROF, handler);

    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_PROF, &timer, NULL);

    while (1)
        ;

    return 0;
}

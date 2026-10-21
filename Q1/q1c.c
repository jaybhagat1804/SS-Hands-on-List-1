#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void handler(int sig)
{
    printf("SIGPROF received\n");
}

int main()
{
    struct itimerval timer;

    signal(SIGPROF, handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    setitimer(ITIMER_PROF, &timer, NULL);

    while (1)
        ;

    return 0;
}

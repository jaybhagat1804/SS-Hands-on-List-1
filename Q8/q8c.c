#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig)
{
    printf("SIGFPE caught\n");
    exit(0);
}

int main()
{
    int a = 10;
    int b = 0;

    signal(SIGFPE, handler);

    printf("%d\n", a / b);

    return 0;
}

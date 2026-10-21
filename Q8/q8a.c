#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig)
{
    printf("SIGSEGV caught\n");
    exit(0);
}

int main()
{
    int *p = NULL;

    signal(SIGSEGV, handler);

    printf("Generating SIGSEGV...\n");

    *p = 10;

    return 0;
}

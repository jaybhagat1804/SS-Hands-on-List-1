#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    signal(SIGINT, SIG_IGN);

    printf("SIGINT ignored. Press Ctrl+C.\n");
    sleep(5);

    signal(SIGINT, SIG_DFL);

    printf("SIGINT restored to default.\n");
    printf("Press Ctrl+C now.\n");

    while (1)
        pause();

    return 0;
}

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT ignored for 5 seconds\n");

    sleep(5);

    sa.sa_handler = SIG_DFL;

    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT restored to default\n");
    printf("Press Ctrl+C\n");

    while (1)
        pause();

    return 0;
}

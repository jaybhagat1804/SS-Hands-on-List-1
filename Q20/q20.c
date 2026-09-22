#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main()
{
    int priority;

    priority = getpriority(PRIO_PROCESS, 0);

    printf("Current nice value: %d\n", priority);

    return 0;
}

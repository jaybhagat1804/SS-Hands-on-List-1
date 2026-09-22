#include <stdio.h>
#include <unistd.h>
#include <sched.h>

int main()
{
    int policy;
    struct sched_param param;

    policy = sched_getscheduler(0);

    if (policy == SCHED_OTHER)
        printf("Current policy: SCHED_OTHER\n");

    else if (policy == SCHED_FIFO)
        printf("Current policy: SCHED_FIFO\n");

    else if (policy == SCHED_RR)
        printf("Current policy: SCHED_RR\n");

    else
        printf("Unknown policy\n");

    param.sched_priority = sched_get_priority_min(SCHED_RR);

    if (sched_setscheduler(0, SCHED_RR, &param) == -1)
    {
        perror("sched_setscheduler");
        return 1;
    }

    printf("Scheduling policy changed to SCHED_RR\n");

    return 0;
}

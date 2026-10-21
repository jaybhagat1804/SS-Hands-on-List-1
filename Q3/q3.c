#include <stdio.h>
#include <sys/resource.h>

int main()
{
    struct rlimit limit;

    if (getrlimit(RLIMIT_NOFILE, &limit) == -1)
    {
        perror("getrlimit");
        return 1;
    }

    printf("Old soft limit: %llu\n",
           (unsigned long long)limit.rlim_cur);

    limit.rlim_cur = 50;

    if (setrlimit(RLIMIT_NOFILE, &limit) == -1)
    {
        perror("setrlimit");
        return 1;
    }

    printf("New soft limit: 50\n");

    return 0;
}

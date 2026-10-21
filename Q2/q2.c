#include <stdio.h>
#include <sys/resource.h>

void print_limit(int resource, char *name)
{
    struct rlimit limit;

    if (getrlimit(resource, &limit) == 0)
    {
        printf("%s:\n", name);

        printf("  Soft limit = %llu\n",
               (unsigned long long)limit.rlim_cur);

        printf("  Hard limit = %llu\n",
               (unsigned long long)limit.rlim_max);
    }
}

int main()
{
    print_limit(RLIMIT_CPU, "CPU time");
    print_limit(RLIMIT_FSIZE, "File size");
    print_limit(RLIMIT_DATA, "Data segment");
    print_limit(RLIMIT_STACK, "Stack");
    print_limit(RLIMIT_CORE, "Core file");
    print_limit(RLIMIT_NOFILE, "Open files");
    print_limit(RLIMIT_NPROC, "Processes");

    return 0;
}

#include <stdio.h>
#include <unistd.h>

unsigned long long rdtsc()
{
    unsigned int low, high;

    __asm__ volatile (
        "rdtsc"
        : "=a"(low), "=d"(high)
    );

    return ((unsigned long long)high << 32) | low;
}

int main()
{
    unsigned long long start, end;

    start = rdtsc();

    getpid();

    end = rdtsc();

    printf("Time taken by getpid = %llu CPU cycles\n", end - start);

    return 0;
}

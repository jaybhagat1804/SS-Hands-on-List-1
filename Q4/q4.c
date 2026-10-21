#include <stdio.h>
#include <unistd.h>

unsigned long long rdtsc()
{
    unsigned int low, high;

    __asm__ volatile(
        "rdtsc"
        : "=a"(low), "=d"(high)
    );

    return ((unsigned long long)high << 32) | low;
}

int main()
{
    unsigned long long start, end;
    int i;

    start = rdtsc();

    for (i = 0; i < 100; i++)
        getppid();

    end = rdtsc();

    printf("100 getppid() calls took %llu CPU cycles\n",
           end - start);

    return 0;
}

#include <stdio.h>
#include <unistd.h>

int main()
{
    execlp("ls", "ls", "-Rl", NULL);

    perror("execlp");

    return 1;
}

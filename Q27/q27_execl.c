#include <stdio.h>
#include <unistd.h>

int main()
{
    execl("/bin/ls", "ls", "-Rl", NULL);

    perror("execl");

    return 1;
}

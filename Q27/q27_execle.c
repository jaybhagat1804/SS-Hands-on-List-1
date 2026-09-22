#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main()
{
    execle("/bin/ls", "ls", "-Rl", NULL, environ);

    perror("execle");

    return 1;
}

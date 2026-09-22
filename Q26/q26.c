#include <stdio.h>
#include <unistd.h>

int main()
{
    execl("./hello", "hello", "Jay", NULL);

    perror("execl");

    return 1;
}

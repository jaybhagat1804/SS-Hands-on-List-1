#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int p1[2];
    int p2[2];

    pid_t pid;

    char parent_msg[] = "Hello Child";
    char child_msg[] = "Hello Parent";

    char buffer[100];

    pipe(p1);
    pipe(p2);

    pid = fork();

    if (pid == 0)
    {
        close(p1[1]);
        close(p2[0]);

        read(p1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        write(p2[1], child_msg, strlen(child_msg) + 1);

        close(p1[0]);
        close(p2[1]);
    }
    else
    {
        close(p1[0]);
        close(p2[1]);

        write(p1[1], parent_msg, strlen(parent_msg) + 1);

        read(p2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);

        close(p1[1]);
        close(p2[0]);
    }

    return 0;
}

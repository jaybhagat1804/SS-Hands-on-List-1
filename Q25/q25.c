#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t children[3];
    int i;

    for (i = 0; i < 3; i++)
    {
        children[i] = fork();

        if (children[i] < 0)
        {
            perror("fork");
            return 1;
        }

        if (children[i] == 0)
        {
            printf("Child %d: PID = %d\n", i + 1, getpid());

            sleep((i + 1) * 2);

            printf("Child %d exiting\n", i + 1);

            exit(0);
        }
    }

    printf("Parent waiting for Child 2...\n");

    waitpid(children[1], NULL, 0);

    printf("Child 2 has finished.\n");

    return 0;
}

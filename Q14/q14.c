#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];
    char message[] = "Hello through pipe";
    char buffer[100];

    pipe(fd);

    write(fd[1], message, strlen(message) + 1);

    read(fd[0], buffer, sizeof(buffer));

    printf("Received: %s\n", buffer);

    close(fd[0]);
    close(fd[1]);

    return 0;
}

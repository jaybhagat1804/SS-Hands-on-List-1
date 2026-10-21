#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd1, fd2;
    char buffer[100];

    fd1 = open("fifo1", O_WRONLY);
    fd2 = open("fifo2", O_RDONLY);

    write(fd1, "Hello from Program 1", 21);

    read(fd2, buffer, sizeof(buffer));

    printf("Program 1 received: %s\n", buffer);

    close(fd1);
    close(fd2);

    return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd1, fd2;
    char buffer[100];

    fd2 = open("fifo2", O_WRONLY);
    fd1 = open("fifo1", O_RDONLY);

    read(fd1, buffer, sizeof(buffer));

    printf("Program 2 received: %s\n", buffer);

    write(fd2, "Hello from Program 2", 21);

    close(fd1);
    close(fd2);

    return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>

int main()
{
    int fd;
    char buffer[100];

    fd = open("myfifo", O_RDONLY | O_NONBLOCK);

    fd_set set;
    struct timeval timeout;

    FD_ZERO(&set);
    FD_SET(fd, &set);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for data for 10 seconds...\n");

    int result = select(fd + 1, &set, NULL, NULL, &timeout);

    if (result == -1)
    {
        perror("select");
    }
    else if (result == 0)
    {
        printf("Timeout: no data received\n");
    }
    else
    {
        read(fd, buffer, sizeof(buffer));
        printf("Received: %s\n", buffer);
    }

    close(fd);

    return 0;
}

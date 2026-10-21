#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char message[] = "Hello from sender";

    fd = open("myfifo", O_WRONLY);

    write(fd, message, strlen(message) + 1);

    close(fd);

    return 0;
}

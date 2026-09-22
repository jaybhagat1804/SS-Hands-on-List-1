#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int ticket;
    FILE *fp;
    struct flock lock;

    fd = open("ticket.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    fcntl(fd, F_SETLKW, &lock);

    fp = fdopen(fd, "r+");

    fscanf(fp, "%d", &ticket);

    ticket++;

    rewind(fp);

    fprintf(fp, "%d\n", ticket);

    fflush(fp);

    printf("New ticket number: %d\n", ticket);

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    fclose(fp);

    return 0;
}

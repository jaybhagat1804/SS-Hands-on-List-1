#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define RECORD_SIZE 100

void lock_record(int fd, int record_no, short type)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_whence = SEEK_SET;
    lock.l_start = (record_no - 1) * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;
    lock.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
    }
}

void unlock_record(int fd, int record_no)
{
    struct flock lock;

    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (record_no - 1) * RECORD_SIZE;
    lock.l_len = RECORD_SIZE;

    fcntl(fd, F_SETLK, &lock);
}

int main()
{
    int fd;
    char record[RECORD_SIZE];

    fd = open("records.txt", O_RDWR | O_CREAT, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    /* Create three records */
    memset(record, 0, RECORD_SIZE);
    strcpy(record, "Record 1");
    write(fd, record, RECORD_SIZE);

    memset(record, 0, RECORD_SIZE);
    strcpy(record, "Record 2");
    write(fd, record, RECORD_SIZE);

    memset(record, 0, RECORD_SIZE);
    strcpy(record, "Record 3");
    write(fd, record, RECORD_SIZE);

    /* Lock record 2 for writing */
    lock_record(fd, 2, F_WRLCK);

    printf("Write lock acquired on Record 2.\n");

    lseek(fd, RECORD_SIZE, SEEK_SET);

    read(fd, record, RECORD_SIZE);

    printf("Current Record 2: %s\n", record);

    /* Modify record 2 */
    lseek(fd, RECORD_SIZE, SEEK_SET);

    memset(record, 0, RECORD_SIZE);
    strcpy(record, "Record 2 Modified");

    write(fd, record, RECORD_SIZE);

    printf("Record 2 modified.\n");

    unlock_record(fd, 2);

    printf("Lock released.\n");

    close(fd);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    key_t key;
    int shmid;
    char *data;

    key = ftok(".", 'B');

    shmid = shmget(key, 1024, IPC_CREAT | 0666);

    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    printf("Shared memory ID = %d\n", shmid);

    data = (char *)shmat(shmid, NULL, 0);

    strcpy(data, "Hello from shared memory");

    printf("Data written: %s\n", data);

    shmdt(data);

    data = (char *)shmat(shmid, NULL, SHM_RDONLY);

    printf("Read-only data: %s\n", data);

    /*
       Do NOT do:
       data[0] = 'X';
       because this attachment is read-only.
    */

    shmdt(data);

    shmctl(shmid, IPC_RMID, NULL);

    printf("Shared memory removed\n");

    return 0;
}

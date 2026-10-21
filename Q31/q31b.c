#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main()
{
    key_t key;
    int semid;
    union semun arg;

    key = ftok(".", 'B');

    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid == -1)
    {
        perror("semget");
        return 1;
    }

    arg.val = 5;

    if (semctl(semid, 0, SETVAL, arg) == -1)
    {
        perror("semctl");
        return 1;
    }

    printf("Counting semaphore created successfully\n");
    printf("Initial value = 5\n");

    return 0;
}

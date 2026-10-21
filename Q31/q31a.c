#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
    int val;
};

int main()
{
    key_t key;
    int semid;
    union semun arg;

    key = ftok(".", 'C');

    semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid == -1)
    {
        perror("semget");
        return 1;
    }

    arg.val = 1;

    semctl(semid, 0, SETVAL, arg);

    printf("Binary semaphore created\n");
    printf("Semaphore ID = %d\n", semid);

    return 0;
}

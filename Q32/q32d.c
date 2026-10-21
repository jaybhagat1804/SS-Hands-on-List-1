#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
    key_t key;
    int semid;

    // Generate the same key as ticket.c
    key = ftok(".", 'A');

    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    // Access the existing semaphore
    semid = semget(key, 1, 0666);

    if (semid == -1)
    {
        perror("semget");
        return 1;
    }

    // Remove the existing semaphore
    if (semctl(semid, 0, IPC_RMID) == -1)
    {
        perror("semctl IPC_RMID");
        return 1;
    }

    printf("Semaphore removed successfully.\n");

    return 0;
}

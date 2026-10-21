#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun
{
    int val;
};

void wait_sem(int semid)
{
    struct sembuf op = {0, -1, 0};

    if (semop(semid, &op, 1) == -1)
    {
        perror("semop wait");
        exit(1);
    }
}

void signal_sem(int semid)
{
    struct sembuf op = {0, 1, 0};

    if (semop(semid, &op, 1) == -1)
    {
        perror("semop signal");
        exit(1);
    }
}

int main()
{
    int shmid, semid;
    int *shared;
    union semun arg;

    // Create shared memory
    shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);

    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    shared = shmat(shmid, NULL, 0);

    if (shared == (void *)-1)
    {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    *shared = 0;

    // Create binary semaphore
    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);

    if (semid == -1)
    {
        perror("semget");
        shmdt(shared);
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    arg.val = 1;

    if (semctl(semid, 0, SETVAL, arg) == -1)
    {
        perror("semctl");
        semctl(semid, 0, IPC_RMID);
        shmdt(shared);
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    // Create two child processes
    for (int i = 0; i < 2; i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            return 1;
        }

        if (pid == 0)
        {
            for (int j = 0; j < 5; j++)
            {
                wait_sem(semid);

                (*shared)++;

                printf("Process %d: Value = %d\n",
                       getpid(), *shared);
                fflush(stdout);

                signal_sem(semid);
            }

            shmdt(shared);
            _exit(0);
        }
    }

    wait(NULL);
    wait(NULL);

    printf("Final shared value = %d\n", *shared);

    shmdt(shared);
    shmctl(shmid, IPC_RMID, NULL);

    // Remove this program's semaphore
    semctl(semid, 0, IPC_RMID);

    printf("Shared memory and semaphore removed.\n");

    return 0;
}

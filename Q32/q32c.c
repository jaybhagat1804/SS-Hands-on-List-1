#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
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
    int semid;
    union semun arg;

    // Create counting semaphore
    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);

    if (semid == -1)
    {
        perror("semget");
        return 1;
    }

    // Initialize with two available resources
    arg.val = 2;

    if (semctl(semid, 0, SETVAL, arg) == -1)
    {
        perror("semctl");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    // Create four child processes
    for (int i = 1; i <= 4; i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            return 1;
        }

        if (pid == 0)
        {
            printf("Process %d waiting for a resource\n", i);
            fflush(stdout);

            wait_sem(semid);

            printf("Process %d acquired a resource\n", i);
            fflush(stdout);

            sleep(2);

            printf("Process %d released a resource\n", i);
            fflush(stdout);

            signal_sem(semid);

            _exit(0);
        }
    }

    // Wait for all four child processes
    for (int i = 0; i < 4; i++)
        wait(NULL);

    // Remove counting semaphore
    semctl(semid, 0, IPC_RMID);

    printf("Counting semaphore removed.\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
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
    key_t key;
    int semid, fd, ticket;
    union semun arg;

    key = ftok(".", 'A');

    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    // Create a new semaphore
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);

    if (semid == -1)
    {
        if (errno == EEXIST)
            printf("Semaphore already exists. Run remove_sem first.\n");
        else
            perror("semget");

        return 1;
    }

    // Initialize binary semaphore to 1
    arg.val = 1;

    if (semctl(semid, 0, SETVAL, arg) == -1)
    {
        perror("semctl SETVAL");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    // Initialize ticket file
    fd = open("ticket.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);

    if (fd == -1)
    {
        perror("open");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    ticket = 100;

    if (write(fd, &ticket, sizeof(ticket)) != sizeof(ticket))
    {
        perror("write");
        close(fd);
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    // Create two child processes
    for (int i = 0; i < 2; i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            close(fd);
            semctl(semid, 0, IPC_RMID);
            return 1;
        }

        if (pid == 0)
        {
            for (int j = 0; j < 5; j++)
            {
                wait_sem(semid);

                lseek(fd, 0, SEEK_SET);

                if (read(fd, &ticket, sizeof(ticket)) != sizeof(ticket))
                {
                    perror("read");
                    _exit(1);
                }

                printf("Process %d: Ticket %d\n",
                       getpid(), ticket);
                fflush(stdout);

                ticket++;

                lseek(fd, 0, SEEK_SET);

                if (write(fd, &ticket, sizeof(ticket)) != sizeof(ticket))
                {
                    perror("write");
                    _exit(1);
                }

                signal_sem(semid);
            }

            close(fd);
            _exit(0);
        }
    }

    // Wait for both children
    wait(NULL);
    wait(NULL);

    close(fd);

    printf("Ticket generation completed.\n");
    printf("Semaphore is still present for Program 4 to remove.\n");

    // Deliberately do not remove the semaphore here.

    return 0;
}

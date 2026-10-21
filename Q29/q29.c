#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key;
    int msqid;

    key = ftok(".", 'A');

    msqid = msgget(key, IPC_CREAT | 0666);

    if (msqid == -1)
    {
        perror("msgget");
        return 1;
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        return 1;
    }

    printf("Message queue removed\n");

    return 0;
}

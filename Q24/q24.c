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

    printf("Key = %d\n", key);
    printf("Message Queue ID = %d\n", msqid);

    return 0;
}

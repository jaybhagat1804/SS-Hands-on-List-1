#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message
{
    long type;
    char text[100];
};

int main()
{
    key_t key;
    int msqid;
    struct message msg;

    key = ftok(".", 'A');

    msqid = msgget(key, IPC_CREAT | 0666);

    msg.type = 1;
    strcpy(msg.text, "Hello from message queue");

    msgsnd(msqid, &msg, strlen(msg.text) + 1, 0);

    printf("Message sent\n");

    return 0;
}

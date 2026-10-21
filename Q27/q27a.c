#include <stdio.h>
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
    msqid = msgget(key, 0666);

    msgrcv(msqid, &msg, sizeof(msg.text), 1, 0);

    printf("Received: %s\n", msg.text);

    return 0;
}

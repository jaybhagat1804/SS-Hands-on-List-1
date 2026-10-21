#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

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
    if(key==-1) {
      perror("ftok");
      return 1;
    }
    
    msqid = msgget(key, IPC_CREAT | 0666);
    if(msqid == -1)
    {
      perror("msgget");
      return 1;
    }
    
    if(msgrcv(msqid, &msg, sizeof(msg.text), 1, IPC_NOWAIT) == -1)
    {
      perror("msgrcv");
      return 1;
    }
    printf("Received: %s\n", msg.text);
    return 0;
}

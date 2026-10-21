#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key;
    int msqid;
    struct msqid_ds info;

    key = ftok(".", 'A');
    if(key==-1)
    {
      perror("ftok");
      return 1;
    }
    

    msqid = msgget(key, IPC_CREAT | 0666);
    if(msqid==-1)
    {
      perror("msgget");
      return 1;
    }

    if (msgctl(msqid, IPC_STAT, &info) == -1)
    {
        perror("msgctl");
        return 1;
    }

    printf("Old permission = %o\n", info.msg_perm.mode);

    info.msg_perm.mode = 0600;

    if (msgctl(msqid, IPC_SET, &info) == -1)
    {
        perror("msgctl");
        return 1;
    }

    printf("New permission = 0600\n");

    return 0;
}

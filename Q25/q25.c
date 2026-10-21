#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key;
    int msqid;
    struct msqid_ds info;

    key = ftok(".", 'A');

    msqid = msgget(key, IPC_CREAT | 0666);

    if (msqid == -1)
    {
        perror("msgget");
        return 1;
    }

    if (msgctl(msqid, IPC_STAT, &info) == -1)
    {
        perror("msgctl");
        return 1;
    }

    printf("Access permission = %o\n", info.msg_perm.mode);
    printf("UID = %d\n", info.msg_perm.uid);
    printf("GID = %d\n", info.msg_perm.gid);

    printf("Last msgsnd time = %ld\n", info.msg_stime);
    printf("Last msgrcv time = %ld\n", info.msg_rtime);
    printf("Last change time = %ld\n", info.msg_ctime);

    printf("Current bytes = %lu\n", info.msg_cbytes);
    printf("Number of messages = %lu\n", info.msg_qnum);
    printf("Maximum bytes = %lu\n", info.msg_qbytes);

    printf("PID of last msgsnd = %d\n", info.msg_lspid);
    printf("PID of last msgrcv = %d\n", info.msg_lrpid);

    return 0;
}

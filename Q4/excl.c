#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{

    int fd;
    fd = open("newFile.txt",O_CREAT | O_EXCL | O_RDWR, 0644);
    
    if(fd==-1)
    {
	perror("open");
        return 1;
}
    printf("File created. FD = %d\n", fd);
    close(fd);

    return 0;
}

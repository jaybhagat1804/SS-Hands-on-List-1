#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	int flags;
	int mode;

	fd = open("file1.txt", O_RDWR);
	if(fd==-1)
	{
		perror("open");
		return 1;
	}
	
	flags = fcntl(fd, F_GETFL);
	mode = flags & O_ACCMODE;

	if(mode == O_RDONLY)
	{
		printf("File is opened in READ ONLY mode.\n");
	}
	else if(mode == O_WRONLY)
	{
		printf("File is opened in WRITE ONLY mode.\n");
	}
	else if(mode == O_RDWR)
	{
		printf("File is opened in READ WRITE mode.\n");
	}
	close(fd);
	return 0;
}

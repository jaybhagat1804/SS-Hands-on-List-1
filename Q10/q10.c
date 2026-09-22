#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	off_t pos;
	fd = open("seekfile.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if(fd == -1)
	{
		perror("open");
		return 1;
	}
	
	write(fd, "ABCDEFGHIJ", 10);
	pos = lseek(fd, 10, SEEK_CUR);
	printf("Return value of lseek = %ld\n", pos);

	write(fd, "1234567890", 10);

	close(fd);
	return 0;
}


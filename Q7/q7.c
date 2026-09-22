#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd1, fd2;
	char buffer[1024];
	int n;

	fd1 = open("file1.txt",O_RDONLY);

	if(fd1 == -1)
	{
		perror("file1");
		return 1;
	}

	fd2 = open("file2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

	if(fd2 == -1)
	{
		perror("file2");
		close(fd1);
		return 1;
	}

	while((n = (fd1, buffer, sizeof(buffer))) > 0)
        {
		write(fd2, buffer, n);

	
	}
	close(fd1);
	close(fd2);

	printf("File copied successfully\n");
	return 0;
	}

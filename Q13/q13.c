#include<stdio.h>
#include<unistd.h>
#include<sys/select.h>

int main()
{
	fd_set readfds;
	struct timeval timeout;
	int result;
	char buffer[100];

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	printf("Waiting for input for 10 seconds...\n");
	result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

	if(result == -1)
		perror("select");
	else if(result==0)
		printf("No input received within 10 seconds.\n");
	else{
		printf("Input is available\n");
		
		read(STDIN_FILENO, buffer, sizeof(buffer));
		printf("You entered: %s", buffer);
	}

	return 0;
}

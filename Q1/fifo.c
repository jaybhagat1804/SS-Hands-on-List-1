#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main()
{
	if(mkfifo("myfifo", 0666) == -1)
		perror("mkfifo");
	else
		printf("FIFO created\n");


return 0;

}

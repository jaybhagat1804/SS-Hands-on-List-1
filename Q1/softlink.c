#include<unistd.h>
#include<stdio.h>

int main()
{
	if(symlink("file1", "softlink") == -1){
		perror("symlink");
	}
	else{
		printf("Soft link created\n");

	}
	return 0;





}


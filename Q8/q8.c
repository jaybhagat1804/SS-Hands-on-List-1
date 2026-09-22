#include<stdio.h>

int main()
{
	FILE *fp;
	char line[200];
	
	fp = fopen("file1.txt", "r");

	if(fp == NULL)
	{
		perror("fopen");
		return 1;
	}

	while(fgets(line, sizeof(line), fp) != NULL)
	{
		printf("%s", line);
	}
	fclose(fp);
	return 0;

}


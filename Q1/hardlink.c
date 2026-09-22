#include <unistd.h>
#include <stdio.h>

int main()
{
   if(link("file1", "hardlink")==-1)
	perror("link");
   else
	printf("Hardlink Created\n");
return 0;
}

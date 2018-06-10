#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<stdlib.h>
int * ch()
{ 
	int *p=malloc(sizeof(int));
	*p=20;
	return p;
}
#define bh (* ch())
int main(int argc ,char*argv[])
{
	/*DIR  *dp;
	struct dirent *dirent;
	if(argc!=2)
	{
		printf("usage: ls directory_name");
		exit(1);
	}
	if((dp=opendir(argv[1]))!=NULL)
	{
		while((dirent=readdir(dp))!=NULL)
			printf("%s",dirent->d_name);
	}*/
	printf("%d",bh);
	
}
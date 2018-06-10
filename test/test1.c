#include<stdio.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main()
{
	int shmid,i;
	shmid=shmget(0x123,1024,0666|IPC_CREAT);
	if(shmid<0)
	{
		perror("shmget\n");
	}
	void *p=shmat(shmid,NULL,0);
	scanf("%d",&i);
	if(i==0)
	{
		shmdt(p);
		shmctl(shmid,IPC_RMID,NULL);
		printf("删除成功\n");
	}
	else if(i==1)
	{
		shmdt(p);
		printf("退出\n");
	}
		
}
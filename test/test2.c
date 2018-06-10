#include<stdio.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

int main()
{
	int shmid,i;
	shmid=semget(0x123,1,0666|IPC_CREAT);
	if(shmid<0)
	{
		perror("shmget\n");
	}
	//void *p=shmat(shmid,NULL,0);
	/*scanf("%d",&i);
	if(i==0)
	{
		shmdt(p);
		shmctl(shmid,IPC_RMID,NULL);
		printf("É¾³ý³É¹¦\n");
	}
	else if(i==1)
	{
		shmdt(p);
		printf("ÍË³ö\n");
	}*/
		
}
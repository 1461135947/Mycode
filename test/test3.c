#include"lib.h"
int main()
{
	int shmid,semid;
	shmid=shmget(0x123,1024,0666|IPC_CREAT);
	if(shmid<0)
	{
		perror("shmget\n");
	}
	if(sem_create(0x123,&semid)<0)
	{
		perror("sem_create");
	}
	int val;
	sem_setval(semid,3);
	printf("%d\n",semid);
	sem_getval(semid,&val);
	printf("%d\n",val);
}
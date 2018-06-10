#include"lib.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
//返回值-1代表出错，0代表semid为空指针，正确返回信号量标识符
int sem_create(int key,int *semid)
{
	
	if(semid==NULL)
	{
		return 0;
	}
	*semid=semget(key,5,0666|IPC_CREAT|IPC_EXCL);
	printf("%d\n",*semid);
	if(*semid<0)
	{
		perror("shmget\n");
		if(errno==EEXIST)
		{
			printf("信号量已存在\n");
			//return errno;
		}
		return -1;
	}
	return *semid;
}
//成功返回信号量标识符，失败返回-1
int sem_open(int key)
{
	int semid;
	semid=semget(key,1,0);
	if(semid<0)
		return -1;
	return semid;
}
//错误返回-1正确返回0
int sem_setval(int semid,int val)
{
	
	union semun su;
	su.val=val;
	if(semctl(semid,0,SETVAL,su)<0)
		return -1;
	else
		return 0;
	
}
//正确返回1,参数错误返回0；
int sem_getval(int semid,int *myval)
{
	int ret = 0;
	int val;
	union semun su;
	val = su.val ;
	//信号量 计数值
	ret = semctl(semid, 0, GETVAL, su);
	printf("%d %d\n",semid,ret);
	if(ret<0)
		perror("semctl");
	//printf("val:%d\n", val);
	
	*myval = ret;
	ret = 0;
	return ret;
}	
int sem_p(int semid)
{
	struct sembuf buf={0,-1,0};
	int ret =0;
	ret=semop(semid,&buf,1);
	return ret;
	
}
int sem_v(int semid)
{
	struct sembuf buf={0,1,0};
	int ret =0;
	ret=semop(semid,&buf,1);
	return ret;
}
#include <pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include <unistd.h>
# define MAX_PRODUCER 1
# define MAX_CONSUMER 2
typedef struct student{
int age;
char *p;
}Student;
int product_count=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void * consumer_run(void *p)
{
	int num=(int)p;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("物品总量：%d\n",product_count);
		while(product_count==0)
		{
			printf("消费者%d开始等待\n",num);
			pthread_cond_wait(&cond,&mutex);
			
		}
		printf("%d号消费者消费物品\n",num);
		--product_count;
		pthread_mutex_unlock(&mutex);
		sleep(3);
	}
}

void * producer_run(void *p)
{
	int num=(int)p;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("%d号生产者生产物品\n",num);
		++product_count;
		printf("物品总量：%d\n",product_count);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(3);
	}
}

int main()
{
	pthread_t thread_id[MAX_CONSUMER+MAX_PRODUCER];
	//void *p;
	//Student student={10,"ABC"};
	for(int i=0;i<MAX_CONSUMER;i++)
	{
		if(pthread_create(&thread_id[i],NULL,consumer_run,(void *)i )<0)
		{
			perror("pthread_create");
			exit(1);
		}
		
	}
	for(int i=MAX_CONSUMER;i<MAX_CONSUMER+MAX_PRODUCER;i++)
	{
		if(pthread_create(&thread_id[i],NULL,producer_run,(void *)i)<0)
		{
			perror("pthread_create");
			exit(1);
		}
		
	}
	for(int i=MAX_CONSUMER;i<MAX_CONSUMER+MAX_PRODUCER;i++)
	{
		pthread_join(thread_id[i],NULL);
	}
	//Student *student_p=(Student *)p;
	//printf("%p\n",*p);
	printf("程序结束\n");
}

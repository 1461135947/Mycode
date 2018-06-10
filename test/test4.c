#include <pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include <unistd.h>
typedef struct student{
int age;
char *p;
}Student;
void * thread_run(void *p)
{
	Student *student;
	student=(Student *)p;
	printf("%d  %s\n",student->age,student->p);
	//printf
	student->age=20;
	student->p="123";
	pthread_exit(p);
}
int main()
{
	pthread_t thread_id;
	void *p;
	Student student={10,"ABC"};
	if(pthread_create(&thread_id,NULL,thread_run,&student)<0)
	{
		perror("pthread_create");
		exit(1);
	}
	pthread_join(thread_id,&p);
	Student *student_p=(Student *)p;
	//printf("%p\n",*p);
	printf("%d %s\n",student_p->age,student_p->p);
}

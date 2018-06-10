#ifndef	__lib_h
#define	__lib_h
#include<unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#define ERR_MSG(error) \
do{ 	\
	printf("%s%s%d: %s\n",__FILE__,__func__,__LINE__,error);\
}while(0)
#define ERR_QUIT(error) \
do{ 	\
	printf("%s%s%d: %s\n",__FILE__,__func__,__LINE__,error);\
	exit(1);\
}while(0)
	
typedef struct{
	char unit[3];  //内存单位
	unsigned int total;  //内存总量
	unsigned int free;   //剩余内存
	
}MEMORY_INFO;	

typedef struct CPU_PACKED         //定义一个cpu occupy的结构体  
{  
char name[20];             	//存放CPU名字  
unsigned int user;        	//user时间
unsigned int nice;        	//nice时间 
unsigned int system;    	//system时间 
unsigned int idle;       	//idle时间  
unsigned int iowait;        //iowait时间
unsigned int irq;       	//irq时间
unsigned int softirq;  		//softtirq时间
}CPU_OCCUPY;  
typedef void Sigfunc(int );
int get_memoccupy(MEMORY_INFO *info);
int get_cpuoccupy(CPU_OCCUPY *info);
int cal_cpuoccupy(CPU_OCCUPY *info_previous,CPU_OCCUPY *info_after);
int get_connect_count(int port);
Sigfunc *signal(int signo,Sigfunc func);	
ssize_t readn(int fd ,void *buff,size_t count);
ssize_t writen(int fd ,void *buff,size_t count);
ssize_t socket_readline(int fd,void *buff,size_t maxlen);

#endif
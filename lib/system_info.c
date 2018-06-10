#include"lib.h"
# define BUFF_SIZE 256
/*
	@info 记录内存信息的结构体
	返回值 成功返回0，出错返回-1
*/
int get_memoccupy(MEMORY_INFO *info)
{
	FILE * file=fopen("/proc/meminfo","r");//从/proc/meminfo读取内存信息
	char name[20],buff[BUFF_SIZE];
	if(info==NULL)
	{
		ERR_MSG("空指针异常");
		return -1;
	}
	if(file==NULL)
	{
		ERR_MSG("文件打开失败");
		return -1;
	}
	fgets(buff,BUFF_SIZE,file);  //读取总内存信息
	sscanf(buff,"%s %u %s",name,&info->total,info->unit);
	fgets(buff,BUFF_SIZE,file);  //读取可用内存信息
	sscanf(buff,"%s %u %s",name,&info->free,info->unit);
	fclose(file);
	return 0;
	
}
/*
	@info 记录CPU信息的结构体
	返回值 成功返回0，出错返回-1
*/
int get_cpuoccupy(CPU_OCCUPY *info)
{
	char buff[BUFF_SIZE];
	FILE * file=fopen("/proc/stat","r");//从/proc/stat读取内存信息
	if(info==NULL)
	{
		ERR_MSG("空指针异常");
		return -1;
	}
	if(file==NULL)
	{
		ERR_MSG("文件打开失败");
		return -1;
	}
	//获取 user、nice、system、idle、iowait、irq、softirq等时间 
	fgets(buff,BUFF_SIZE,file);
	sscanf(buff,"%s %u %u %u %u %u %u %u",info->name,&info->user,&info->nice,&info->system,&info->idle,&info->iowait,&info->irq,&info->softirq);
	fclose(file);
	return 0;
	
}
/*
	根据两个时间点的CPU信息计算出CPU的使用率，两个时间点的间隔越大计算的CPU使用率越准确
	@info_previous 前一个时间的CPU信息
	@info_after 后一个时间的CPU信息
	返回值:成功返回CPU的使用率，出错返回-1
*/
int cal_cpuoccupy(CPU_OCCUPY *info_previous,CPU_OCCUPY *info_after)
{
	unsigned long sum_previous,sum_after,total,idle;
	if(info_previous==NULL||info_after==NULL)
	{
		ERR_MSG("空指针异常");
		return -1;
	}
	//计算前一个CPU时间的总和
	sum_previous=info_previous->user+info_previous->nice+info_previous->system+info_previous->idle+info_previous->softirq+info_previous->iowait+info_previous->irq;
	//计算后一个CPU时间的总和
	sum_after=info_after->user+info_after->nice+info_after->system+info_after->idle+info_after->iowait+info_after->softirq+info_after->irq;
	total=sum_after-sum_previous;
	idle=info_after->idle-info_previous->idle;
	if(total==0)
		return 0;
	else
		return (total-idle)*100/total;
	
	
}
/*
	子进程回收函数
*/
void thread_handle(int num)
{
	while(waitpid(0,NULL,WNOHANG)>0)  //循环回收子进程，防止在瞬间多个子进程发送SIGCHLD,而父进程不能及时处理的情况
		;
}

/*
@port 需要检测的端口 0代表通配端口
返回值 成功返回端口的连接数，出错返回-1
*/
int get_connect_count(int port)
{
	int connect_count=0;
	char buff[256];
	char _port[6]={0};
	if(port<0||port>65535) //错误端口
	{
		ERR_MSG("端口错误");
		return -1;
	}
	if(port==0)
		strcpy(_port,"\"*\"");
	else
		sprintf(_port,"%d",port);
	printf("%s\n",_port);
	//signal(SIGCHLD);
	pid_t fd;
	//int file=open("./connect_count",O_RDWR|O_CREAT,0777);
	unlink("/tmp/connect_count1");
	if(mkfifo("/tmp/connect_count1",0666)<0)
	{
		//printf("%d \n",errno,EACCES);
		ERR_QUIT(strerror(errno));
	}
	fd=fork(); 
	if(fd<0)
	{
		ERR_QUIT(strerror(errno));
	}
	else if(fd>0)  //父进程
	{
		fd=fork(); 
		if(fd<0)
		{
			ERR_QUIT(strerror(errno));
		}
		else if(fd>0)//父进程
		{
			int i=2;
			while(i>0) //回收创建的子进程
			{
				printf("回收子进程成功\n");
				--i;
				printf("%d\n",wait(NULL));
			}
			FILE * file=fopen("./connect_count_output","r+");
			while(fgets(buff,256,file))
				++connect_count;			
			fclose(file);
		    unlink("/tmp/connect_count1");
			unlink("./connect_count_output");
			return connect_count-2;	
		}
		else  //第二个子进程
		{
			int file_in=open("./connect_count_input",O_RDWR|O_CREAT,0777);
			if(file_in<0)
				ERR_QUIT(strerror(errno));
			int file_out=open("./connect_count_output",O_RDWR|O_CREAT,0777);
			if(file_out<0)
				ERR_QUIT(strerror(errno));
			int _file=open("/tmp/connect_count1",O_RDONLY);
			//fgets(buff,256,fdopen(_file,"r+"));		
			int len;		
			while((len=read(_file,buff,256))>0)
				write(file_in,buff,len);		
			close(_file);
			close(file_in);	
			dup2(file_out,STDOUT_FILENO);
			unlink("./connect_count_input");
			execlp("grep","grep","-i",_port,"./connect_count_input",NULL);
			//execlp("cat","cat",NULL);
		}	
	}
	else   //第一个子进程
	{
		int file=open("/tmp/connect_count1",O_WRONLY);
		if(file<0)
			ERR_QUIT(strerror(errno));
		dup2(file,STDOUT_FILENO);
		execlp("netstat","netstat","-nat",NULL);
	}
}
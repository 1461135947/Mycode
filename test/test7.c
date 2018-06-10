#include"lib.h"

int main()
{
	pid_t fd;
	MEMORY_INFO info;
	CPU_OCCUPY cpu1,cpu2;
	if(get_memoccupy(&info)<0)
	{
		printf("获取内存信息失败\n");
	}
	else
	{
		printf("内存总大小：%d  %s剩余内存：%d  %s \n",info.total,info.unit,info.free,info.unit);
	}
	/*get_cpuoccupy(&cpu1);
	usleep(300*1000);
	get_cpuoccupy(&cpu2);
	printf("CPU使用率:%d %%\n",cal_cpuoccupy(&cpu1,&cpu2));*/
	get_cpuoccupy(&cpu1);
	sleep(1);
	get_cpuoccupy(&cpu2);
	printf("CPU使用率:%d %%\n",cal_cpuoccupy(&cpu1,&cpu2));
	/*fd=fork();
	if(fd<0)
	{
		perror("fork");
		exit(1);
	}
	else if(fork==0)
	{
		wait(NULL);
	}
	else
	{
		
	}*/
	printf("端口连接数:%d\n",get_connect_count(0)); 
	
}
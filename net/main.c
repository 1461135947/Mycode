#include"net.h"
int main()
{
	int i=20;
	void *net;
	init(&net);
	printf("初始状态：\n");
	print(net);
	while(i>0)
	{
		printf("第%d 次交换后\n",21-i);
		riot(net);	
		print(net);
		
		sleep(1);
		--i;
	}
	destory(net);
}
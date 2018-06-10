#include"net.h"

/*
出错函数封装
*/
void error(char *error,int error_number)
{
	perror(error);
	exit(error_number);
}
void init(void **_net)
{
	int fd;
	char buff[1024];
	//分配内存
	Net *net=(Net *)malloc(sizeof(Net));
	*_net=net;
	if(net==NULL)
	{
		error("malloc",3);
	}
	for(int i=0;i<ROUTE_MAX;i++)
	{
		net->route[i]=NULL;
	}
	net->route_count=0;
	fd=open("./net.txt",O_RDWR);
	if(fd<0)
	{
		error("open",1);
	}
	//打开文件
	FILE *file=fdopen(fd,"r+");
	if(file==NULL)
	{
		error("fdopen",2);
	}
	while(fgets(buff,1024,file))  //读取文本行
	{
		
		int i=0,j,net_number;
		int index[ROUTE_MAX];
		memset(index,0,sizeof(int)*ROUTE_MAX);
		buff[strlen(buff)-1]=0;
		//字符串切割 提取信息
		char *string_buff[100];
		string_buff[i++]=strtok(buff," ");
		while((string_buff[i]=strtok(NULL," "))!=NULL)
		{
			++i;
		}
		i=0;
		
		while(string_buff[i] !=NULL)  //初始化路由表将网络编号记录在路由表中
		{
			j=atoi(string_buff[i]);
			if(i==0)
			{
				net_number=j;
				printf("%d\n",j);
			}
			else 
			{
				if(net->route[j-1]==NULL)  //Route结构体的初始化
				{
					net->route[j-1]=malloc(sizeof(Route));
					if(net->route[j-1]==NULL)
						error("malloc",5);
					net->route_count=j>net->route_count?j:net->route_count;
					sprintf(net->route[j-1]->name,"路由器%d",j);
					memset(net->route[j-1]->net_distance,-1,sizeof(int )*NET_MAX);
				    net->route[j-1]->next_route_count=0;
				}
				//记录网络编号到路由表中
				net->route[j-1]->net_distance[net_number-1]=1;
				strcpy(net->route[j-1]->net_arrive[net_number-1],"直连");
			}
			index[i++]=j;
		}
		int size=i;
		for(int i=1;i<size;i++)   //建立路由器之间的连接
		{
			Route * route=net->route[index[i]-1];
				//printf("%p\n",route);
			for(int j=1;j<size;j++)
			{
				
				if(i!=j)
			    {	
					route->next_route[route->next_route_count++]=net->route[index[j]-1];
				}
			}
		}
	}
}
//销毁路由表释放内存
void destory(void *net)
{
	Net * _net=net;
	for(int i=0;i<_net->route_count;i++)
		free(_net->route[i]);
	free(_net);
	printf("销毁成功\n");
}
/*
  对所有路由表进行初始化
*/
void riot(void *net)
{
	Net * _net=(Net *)net;
	for(int i=0;i<_net->route_count;i++)
	{
		Route *route=_net->route[i];
		if(route==NULL) //跳过不存在的路由器
			continue;
		for(int j=0;j<route->next_route_count;j++)
		{
			Route *next_route=route->next_route[j];
			if(next_route==NULL) //跳过不存在的路由器
				continue;
			for(int k=0;k<NET_MAX;k++)
			{
				if(next_route->net_distance[k]>0)  //选出路由器可到达的网络
				{
					if(strcmp(next_route->name,route->net_arrive[k])==0)   //如果下一条地址为交换路由器  直接更新
					{
						route->net_distance[k]=next_route->net_distance[k]+1;
						//strcpy(route->net_arrive[k],next_route->name);
					}
					else     //如果交换路由表路径更短则更新路由表
					{
						if(route->net_distance[k]<0||(next_route->net_distance[k]+1)<route->net_distance[k])
						{
							route->net_distance[k]=next_route->net_distance[k]+1;
							strcpy(route->net_arrive[k],next_route->name);
						}
						
					}
				}
			}
		}
	}
}
//打印路由表
void print(void *net)
{
	 Net * _net=net;
	 for(int i=0;i<_net->route_count;i++)
	 {
		 Route *route=_net->route[i];
		 if(route==NULL)
			 continue;
		 printf("%s\n",route->name);
		 for(int j=0;j<NET_MAX;j++)
		 {
			 char buff[1024];
			 if(route->net_distance[j]>0)
			 {
				 sprintf(buff,"网络%d:距离:%d  下一跳:%s\n",j+1,route->net_distance[j],route->net_arrive[j]); 
				 write(1,buff,strlen(buff));
			 }	 
			 //printf("456\n");
		 }
		 printf("\n");
	 }
	 
}

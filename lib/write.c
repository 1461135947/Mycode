#include"lib.h"
/*
	将n个字节的数据写入文件描述符中
	成功则返回写入的总字节个数，失败返回-1
	@fd 需要写入的文件描述符
	@buff 写入数据的内存首地址
	@count 写入数据的长度
*/
ssize_t writen(int fd ,void *buff,size_t count)
{
	ssize_t nwrite=0,nleft=count;//nleft剩余未读完字节的个数 nread一次读取成功的字节个数
	char * write_buff=buff;  
	while(nleft>0)
	{
		nwrite=write(fd,buff,nleft);
		if(nread<0)
		{
			if(errno=EINTR)//如果被信号中断则继续写入
				continue;
			return -1; //写入失败
		}
		read_buff+=nread;
		nleft-=nread;
	}
	return count;
}

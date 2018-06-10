#include"lib.h"
/*
	从文件描述符中读取n个字节的数据
	成功则返回写入的总字节个数，失败返回-1，
	@fd 需要读取的文件描述符
	@buff 接受数据的内存首地址
	@count 读取数据的长度
*/
ssize_t readn(int fd ,void *buff,size_t count)
{
	ssize_t nread=0,nleft=count;//nleft剩余未读完字节的个数 nread一次读取成功的字节个数
	
	char * read_buff=buff;  
	while(nleft>0)
	{
		nread=read(fd,read_buff,nleft);
		if(nread<0)
		{
			if(errno=EINTR)//如果被信号中断则继续读取
				continue;
			return -1; //读取失败	
		}
		else if(nread==0)  //遇到文件结束符（Tcp协议中对方关闭连接）
		{
			return count-nleft;
		}
		read_buff+=nread;
		nleft-=nread;
	}
	return count;
}
/*
	从指定套接字字中读取一行文本,最多读取maxlen字节（包含'\0'），文本以'\0'结尾
	成功则返回读取字节的个数，失败返回-1，
	@fd 需要读取的文件描述符
	@buff 接受数据的内存首地址
	@maxlen 允许读取的最大字节个数
	
*/
ssize_t socket_readline(int fd,void *buff,size_t maxlen)
{
	int i=0;
	ssize_t nread=0,nleft=maxlen-1;//nleft缓冲区剩余的字节 nread已读取成功的字节个数
	char *read_buff=buff;
	while(nleft>0)
	{
		//检测缓冲区是否有数据
		nread=recv(fd,read_buff,nleft,MSG_PEEK);
		if(nread<0)  //出错
		{
			if(errno==EINTR)
			{
				continue;
			}
			return -1;
		}
		else if(nread==0)
		{
			*buff='\0';
			return maxlen-nleft-1;
		}
		i=0;
		while(i<nread&&read_buff[i++]!='\n')
			;
		if(i!=nread)  //检测到\n结束检测
		{	
			nread=readn(fd,read_buff,i);
			if(nread<0) //读取失败
				return -1;
			*read_buff[nread]='\0';
			return maxlen-1-nleft+nread;
		}
	    //在检测的数据中没有'\n'继续检测
		nread=readn(fd,read_buff,i);
		if(nread<0)  //读取失败
			return -1;
		else if(nread!=i)  //读取的字节数不足  直接返回
		{
			read_buff[nread]='\0';
			return maxlen-1-nleft+nread;
		}	
		nleft-nread;
		read_buff+=nread;
	}
	//maxlen字节中没有\n返回一个空字符串
	*read_buff='\0';
	return maxlen-nleft-1;
}
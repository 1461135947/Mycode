#include"lib.h"
/*
	���ļ��������ж�ȡn���ֽڵ�����
	�ɹ��򷵻�д������ֽڸ�����ʧ�ܷ���-1��
	@fd ��Ҫ��ȡ���ļ�������
	@buff �������ݵ��ڴ��׵�ַ
	@count ��ȡ���ݵĳ���
*/
ssize_t readn(int fd ,void *buff,size_t count)
{
	ssize_t nread=0,nleft=count;//nleftʣ��δ�����ֽڵĸ��� nreadһ�ζ�ȡ�ɹ����ֽڸ���
	
	char * read_buff=buff;  
	while(nleft>0)
	{
		nread=read(fd,read_buff,nleft);
		if(nread<0)
		{
			if(errno=EINTR)//������ź��ж��������ȡ
				continue;
			return -1; //��ȡʧ��	
		}
		else if(nread==0)  //�����ļ���������TcpЭ���жԷ��ر����ӣ�
		{
			return count-nleft;
		}
		read_buff+=nread;
		nleft-=nread;
	}
	return count;
}
/*
	��ָ���׽������ж�ȡһ���ı�,����ȡmaxlen�ֽڣ�����'\0'�����ı���'\0'��β
	�ɹ��򷵻ض�ȡ�ֽڵĸ�����ʧ�ܷ���-1��
	@fd ��Ҫ��ȡ���ļ�������
	@buff �������ݵ��ڴ��׵�ַ
	@maxlen �����ȡ������ֽڸ���
	
*/
ssize_t socket_readline(int fd,void *buff,size_t maxlen)
{
	int i=0;
	ssize_t nread=0,nleft=maxlen-1;//nleft������ʣ����ֽ� nread�Ѷ�ȡ�ɹ����ֽڸ���
	char *read_buff=buff;
	while(nleft>0)
	{
		//��⻺�����Ƿ�������
		nread=recv(fd,read_buff,nleft,MSG_PEEK);
		if(nread<0)  //����
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
		if(i!=nread)  //��⵽\n�������
		{	
			nread=readn(fd,read_buff,i);
			if(nread<0) //��ȡʧ��
				return -1;
			*read_buff[nread]='\0';
			return maxlen-1-nleft+nread;
		}
	    //�ڼ���������û��'\n'�������
		nread=readn(fd,read_buff,i);
		if(nread<0)  //��ȡʧ��
			return -1;
		else if(nread!=i)  //��ȡ���ֽ�������  ֱ�ӷ���
		{
			read_buff[nread]='\0';
			return maxlen-1-nleft+nread;
		}	
		nleft-nread;
		read_buff+=nread;
	}
	//maxlen�ֽ���û��\n����һ�����ַ���
	*read_buff='\0';
	return maxlen-nleft-1;
}
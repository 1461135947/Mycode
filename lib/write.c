#include"lib.h"
/*
	��n���ֽڵ�����д���ļ���������
	�ɹ��򷵻�д������ֽڸ�����ʧ�ܷ���-1
	@fd ��Ҫд����ļ�������
	@buff д�����ݵ��ڴ��׵�ַ
	@count д�����ݵĳ���
*/
ssize_t writen(int fd ,void *buff,size_t count)
{
	ssize_t nwrite=0,nleft=count;//nleftʣ��δ�����ֽڵĸ��� nreadһ�ζ�ȡ�ɹ����ֽڸ���
	char * write_buff=buff;  
	while(nleft>0)
	{
		nwrite=write(fd,buff,nleft);
		if(nread<0)
		{
			if(errno=EINTR)//������ź��ж������д��
				continue;
			return -1; //д��ʧ��
		}
		read_buff+=nread;
		nleft-=nread;
	}
	return count;
}

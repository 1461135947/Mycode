#include"lib.h"
/*
Ϊ�ź�ע�ᴦ����
@signo ��Ҫע����ź�
@func  �ź�������Ĵ�����
�ɹ����ؾɵ��źŴ�������������SIG_ERR
*/

Sigfunc *signal(int signo,Sigfunc *func)
{
	struct sigaction _old,_new;
	_new.sa_handler=func;
	sigemptyset(&_new.sa_mask);
	_new.sa_flags=0;
	if(sigaction(signo,&_new,&_old)<0)
	{	
		return SIG_ERR;
	}
	return _old.sa_handler;	
}

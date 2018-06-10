#include"lib.h"
/*
为信号注册处理函数
@signo 需要注册的信号
@func  信号相关联的处理函数
成功返回旧的信号处理函数，出错返回SIG_ERR
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

#ifndef	__net_h
#define	__net_h
# define ROUTE_MAX 100
# define NET_MAX 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
typedef struct route
{
	char name[100];
	int net_distance[NET_MAX];
	char  net_arrive[100][NET_MAX];
	struct route * next_route[NET_MAX];
	int next_route_count;
	
}Route;

typedef struct net
{
	Route * route[ROUTE_MAX];
	int route_count;
	
}Net;
void init(void **_net);
void error(char *error,int error_number);
void destory(void *net);
void print(void *net);
void riot(void *net);
#endif
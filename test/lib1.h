#ifndef _LIB_H_
#define _LIB_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>

 union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };


int sem_create(int key,int *semid);
int sem_open(int key);
int sem_setval(int semid,int val);
int sem_getval(int semid,int *val);
int sem_p(int semid);
int sem_v(int semid);
#endif
#ifndef __INIT_H__
#define __INIT_H__


#include "head.h"


/*
 * 读取配置文件进行初始化
 * confFilePath：配置文件路径
 * socketFd：传出参数，读取配置文件后初始化好的socketFd
 * processNum：传出参数，从配置文件中读取的最大进程数
 * */
int confInit(char *confFilePath,int *socketFd,int *processNum);


/*
 * 初始化日志文件描述符，进程间通过进程锁互斥访问该文件描述符
 * logFd：传出参数，日志文件描述符
 * */
int logFileInit(int *logFd);


/*
 * 初始化进程池
 * processInfo：指向管理进程使用的结构体数组的指针
 * processNum：最大进程数
 * */
int processPoolInit(pProcessData_t processInfo,int processNum);

/*
 * epollFd：注册的epoll
 * fd：带注册的描述符 
 * */
int epollAdd(int epollFd,int fd);



#endif




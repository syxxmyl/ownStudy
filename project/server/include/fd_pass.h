#ifndef __FD_PASS_H__
#define __FD_PASS_H__

#include "head.h"

/*
 * 传输文件描述符
 * 
 * */
int sendFd(int pipeFd,int newClientFd,char childExitFlag);

/*
 * 接收文件描述符
 * */
int recvFd(int pipeFd,int *newClientFd,char* childExitFlag);


#endif

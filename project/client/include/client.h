#ifndef __INTI_H__
#define __INTI_H__

#include "head.h"


/*
 * 初始化socket连接
 * 
 * */
int confInit(char *confFilePath,int *socketFd);


/*
 * 登录至服务器
 * */
int userLogin(int socketFd);


/*
 * 发送请求给服务器端，在这里做一次命令校验
 * */
int sendClientRequest(int socketFd);


int cmdPwd(int,char *);


int cmdCd(int,char *);


int cmdLs(int);


int cmdMkdir(int,char *);


int cmdRemove(int,char *);


int cmdPuts(int,char *);


int cmdGets(int,char *);

#endif



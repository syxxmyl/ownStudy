#ifndef __CHILD_OP_H__
#define __CHILD_OP_H__

#include "head.h"

/*
 * 用户验证函数
 * while循环直到验证成功才会break结束
 * username 传出参数，用来给下面的切换路径用
 * */
int userValidate(int clientSocketFd,char *username);


/*
 * 切换工作路径到个人目录
 * preDir:确保每次接到新客户端的当前路径都相同
 * */
int changeDirToUserOwn(char *username,char *preDir);


/*
 * 处理客户端发来的请求
 * logFd：日志文件描述符
 * preDir：用来在cd里规避超过用户的目录
 * username：用来记录日志
 * */
int recvClientRequest(int clientSocketFd,int logFd,char *preDir,char *username);


/*
 * 子进程处理函数
 * */
int childHandle(int pipeFd);




#endif

#ifndef __HEAD_H__

#define __HEAD_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <strings.h>
#include <syslog.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <sys/uio.h>
#include <sys/sendfile.h>

#define ARGS_CHECK(argc,val) {if(argc!=val)  {printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retVal,funcName) {if(ret==retVal) {perror(funcName);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcName) {if(ret!=0) {printf("%s:%s\n",funcName,strerror(ret));return -1;}}
#define CHILD_THREAD_ERROR_CHECK(ret,funcName) {if(ret!=0) {printf("%s:%s\n",funcName,strerror(ret));return (void*)-1;}}



typedef struct {
    int cmdType;    
    /*
     *     数据传输的类型
     *     0    用户名
     *     1    密码
     *     2    cd操作
     *     3    ls操作
     *     4    puts操作
     *     5    gets操作
     *     6    remove操作
     *     7    pwd操作
     *     8    mkdir操作
     *     9    文件传输数据
     *     10   断点续传
     */
    int datalen;        //buf的长度
    char buf[1000];     //可能需要传递的数据，如用户名、密码、目录名、文件名等


}train_t,pTrain_t;


/*
 *  * 循环接收
 *   * */
int recvCycle(int sfd,void* buf,int recvLen);

#endif 


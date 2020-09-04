#include "../include/init.h"
#include "../include/fd_pass.h"
#include "../include/child_op.h"

int confInit(char *confFilePath,int *socketFd,int *processNum){
    FILE *fd=fopen(confFilePath,"rb+");
    char ip[20]={0};
    int port;
    int ret=fscanf(fd,"ip=%s\nport=%d\nprocessNum=%d",ip,&port,processNum);
    printf("ip=%s,port=%d,processNum=%d\n",ip,port,*processNum);
    int sfd;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(port);
    serAddr.sin_addr.s_addr=inet_addr(ip);
    int reuse=1;
    ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    ret=bind(sfd,(struct sockaddr *)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sfd,*processNum);
    *socketFd=sfd;
    fclose(fd);
    return 0;
}

int logFileInit(int *logFd){
    int sfd=open("../bin/logFile",O_RDWR|O_APPEND);//追加到文件末尾
    ERROR_CHECK(sfd,-1,"openLogFile");
    *logFd=sfd;
    return 0;
}

int processPoolInit(pProcessData_t processInfo,int processNum){
    int i;
    pid_t pid;
    int fds[2];
    int ret;
    for(i=0;i<processNum;i++){
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(pid==0){
            close(fds[0]);
            childHandle(fds[1]);
        }else{
            close(fds[1]);
            processInfo[i].pid=pid;
            processInfo[i].pipeFd=fds[0];
            processInfo[i].busy=0;
        }
    }
    return 0;
}

int epollAdd(int epollFd,int fd){
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.fd=fd;
    int ret;
    ret=epoll_ctl(epollFd,EPOLL_CTL_ADD,fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}

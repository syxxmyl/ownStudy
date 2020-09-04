#define _GNU_SOURCE
#include "../include/client.h"

int cmdPwd(int fd,char *dir){
    train_t train;
    bzero(&train,sizeof(train));
    train.cmdType=7;
    send(fd,&train.cmdType,4,0);
    bzero(&train,sizeof(train));
    recvCycle(fd,&train.cmdType,4);
    recvCycle(fd,&train.datalen,4);
    recvCycle(fd,train.buf,train.datalen);
    strcpy(dir,train.buf);
    return 0;
}

int cmdCd(int fd,char *args){
    train_t train;
    bzero(&train,sizeof(train));
    train.cmdType=2;
    train.datalen=strlen(args);
    strcpy(train.buf,args);
    send(fd,&train,train.datalen+8,0);
    char flag;
    recvCycle(fd,&flag,1);
    if(flag==0){
        printf("进入目录错误\n");
        return 0;
    }
    char dir[100]={0};
    recvCycle(fd,&train.cmdType,4);
    recvCycle(fd,&train.datalen,4);
    recvCycle(fd,dir,train.datalen);
    return 0;
}

int cmdLs(int fd){
    train_t train;
    bzero(&train,sizeof(train_t));
    train.cmdType=3;
    send(fd,&train.cmdType,4,0);
    char dir[1000]={0};
    bzero(&train,sizeof(train));
    recvCycle(fd,&train.cmdType,4);
    recvCycle(fd,&train.datalen,4);
    recvCycle(fd,dir,train.datalen);
    printf("%s\n",dir);
    return 0;
}

int cmdMkdir(int fd,char *args){
    train_t train;
    bzero(&train,sizeof(train));
    train.cmdType=8;
    train.datalen=strlen(args);
    strcpy(train.buf,args);
    send(fd,&train,train.datalen+8,0);
    return 0;
}

int cmdRemove(int fd,char *args){
    train_t train;
    bzero(&train,sizeof(train));
    train.cmdType=6;
    train.datalen=strlen(args);
    strcpy(train.buf,args);
    send(fd,&train,train.datalen+8,0);
    return 0;
}
int cmdPuts(int fd,char* args )
{
    train_t train;
    memset(&train,0,sizeof(train));
    train.cmdType=4;
    send(fd,&train.cmdType,4,0);    //服务器端接收类型
    int fileFd=open(args,O_RDWR);
    /*如果打开文件失败，则发送错误给服务器通知不用再接收了*/
    char flag=0;
    if(fileFd==-1){
        printf("文件打开失败\n");
        send(fd,&flag,1,0);//0表示失败
        return 0;
    }else{
        flag=1;
        send(fd,&flag,1,0);//1表示成功
    }
    //传递文件名
    train.datalen=strlen(args);
    strcpy(train.buf,args);
    send(fd,&train,train.datalen+8,0);
    bzero(&train,sizeof(train));
    //传递文件大小
    struct stat file;
    fstat(fileFd,&file);
    train.datalen=sizeof(file.st_size);
    memcpy(train.buf,&file.st_size,train.datalen);
    send(fd,&train,train.datalen+8,0);
    //传递文件内容
    sendfile(fd,fileFd,NULL,file.st_size);
    printf("send success,size=%ld\n",file.st_size);
    close(fileFd);
    return 0;
}

int cmdGets(int fd,char *args){
    train_t train;
    bzero(&train,sizeof(train));
    //传递待下载文件名
    train.cmdType=5;
    train.datalen=strlen(args);
    strcpy(train.buf,args);
    send(fd,&train,train.datalen+8,0);
    //接收请求是否成功
    char flag=0;
    recvCycle(fd,&flag,1);
    if(flag==0){
        printf("请求下载失败\n");
        return 0;
    }else{
        //首先判断是否已经有该文件了，如果已经有了则传递当前下载的字节数给服务器端，再偏移到该位置继续等待下载
        struct stat buf;
        stat(args,&buf);
        train.cmdType=10;
        train.datalen=sizeof(buf.st_size);
        memcpy(train.buf,&buf.st_size,train.datalen);
        send(fd,&train,train.datalen+8,0);
        //接收文件大小
        bzero(&train,sizeof(train));
        recvCycle(fd,&train.cmdType,4);
        recvCycle(fd,&train.datalen,4);
        off_t fileSize=0;
        recvCycle(fd,&train.buf,train.datalen);
        memcpy(&fileSize,&train.buf,train.datalen);
        //接收文件
        int fileFd=open(args,O_CREAT|O_RDWR,0666);
        ERROR_CHECK(fileFd,-1,"file recv open");
        lseek(fileFd,buf.st_size,SEEK_SET);
        off_t downLoadSize=0;
        int ret;
        int fds[2];
        pipe(fds);
        while(downLoadSize<fileSize){
            ret=splice(fd,NULL,fds[1],NULL,fileSize-downLoadSize,SPLICE_F_MOVE|SPLICE_F_MORE);
            ERROR_CHECK(ret,-1,"splice");
            splice(fds[0],NULL,fileFd,NULL,ret,SPLICE_F_MOVE|SPLICE_F_MORE);
            downLoadSize+=ret;
        }
        printf("downLoad finished\n");
        close(fds[0]);
        close(fds[1]);
        close(fileFd);
    }
    return 0;
}

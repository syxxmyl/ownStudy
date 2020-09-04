#include "../include/child_op.h"
#include "../include/fd_pass.h"
#include "../include/cmd.h"
#include "../include/init.h"

int childHandle(int pipeFd){
    int newFd;
    char childExitFlag;
    char finishFlag;
    train_t train;
    char username[20]={0};
    char preDir[100]={0};
    char ownDir[100]={0};//子进程本身的路径
    strcpy(preDir,getcwd(NULL,0));
    strcpy(ownDir,getcwd(NULL,0));
    /*注册logFd*/
    int logFd=0; 
    int ret=0;
    char loginFlag=0;
    while(1){
        logFileInit(&logFd);
        printf("logFd=%d\n",logFd);
        bzero(&train,sizeof(train));
        loginFlag=0;
        recvFd(pipeFd,&newFd,&childExitFlag);
        printf("newFd=%d\n",newFd);
        if(childExitFlag){
            exit(0);
        }
        while(1){
            bzero(&username,sizeof(username));
            bzero(&train,sizeof(train));
            ret=recvCycle(newFd,&train.cmdType,sizeof(int));
            if(ret==-1){
                break;
            }
            recvCycle(newFd,&train.datalen,sizeof(int));
            recvCycle(newFd,&train.buf,train.datalen);
            strcpy(username,train.buf);
            ret=userValidate(newFd,username);
            if(ret==-1){
                printf("loginFlag=%d\n",loginFlag);
                send(newFd,&loginFlag,1,0);//0表示校验错误
            }else{
                loginFlag=1;//1表示校验成功
                printf("loginFlag=%d\n",loginFlag);
                send(newFd,&loginFlag,1,0);
                break;
            }
        }
        writeIntoLog(logFd,username,"login");
        /*在这里切换路径*/
        changeDirToUserOwn(username,preDir);
        char preDir[100]={0};//局部变量，在while循环的本句之后使用preDir就是这个了，之前的是上面定义的preDir
        strcpy(preDir,getcwd(NULL,0));
        recvClientRequest(newFd,logFd,preDir,username);
        writeIntoLog(logFd,username,"logout");
        chdir(ownDir);
        printf("newfd=%d,logfd=%d\n",newFd,logFd);
        close(newFd);
        close(logFd);
        write(pipeFd,&finishFlag,1);
    }
    return 0;
}

int userValidate(int clientSocketFd,char *username){
    train_t train;
    char userPass[20]={0};
    bzero(&train,sizeof(train));
    recvCycle(clientSocketFd,&train.cmdType,sizeof(int));
    recvCycle(clientSocketFd,&train.datalen,sizeof(int));
    recvCycle(clientSocketFd,&train.buf,train.datalen);
    bzero(&userPass,sizeof(userPass));
    strcpy(userPass,train.buf);
    int ret=0;
    FILE *fp=fopen("../conf/user.conf","rb");
    ERROR_CHECK(fp,NULL,"fopen user conf");
    char name[20]={0};
    char password[20]={0};
    while(ret!=-1){
        bzero(&name,20);
        bzero(&password,20);
        ret=fscanf(fp,"name=%s\npassword=%s\n",name,password);
        if(strcmp(username,name)==0){
            if(strcmp(password,userPass)==0){
                fclose(fp);
                printf("验证成功\n");
                return 0;
            }
        }
    }
    printf("验证失败\n");
    fclose(fp);
    return -1;
}

int changeDirToUserOwn(char *username,char *preDir){
    char dir[100]={0};
    int ret;
    sprintf(dir,"%s%s%s",preDir,"/../bin/",username);
    ret=chdir(dir);
    ERROR_CHECK(ret,-1,"chdir");
    return 0;
}

int recvClientRequest(int fd,int logFd,char *preDir,char *username){
    train_t train;
    int ret;
    while(1){
        bzero(&train,sizeof(train));
        ret=recvCycle(fd,&train.cmdType,sizeof(int));
        if(ret==-1){
            break;
        }
        printf("cmdType=%d\n",train.cmdType);
        switch(train.cmdType){
        case 2:{
                   writeIntoLog(logFd,username,"cd");
                   cmdCd(fd,preDir);
                   break;
               }
        case 3:{
                   writeIntoLog(logFd,username,"ls");
                   cmdLs(fd);
                   break;
               }
        case 4:{
                   writeIntoLog(logFd,username,"puts");
                   cmdPuts(fd);
                   break;
               }
        case 5:{
                   writeIntoLog(logFd,username,"gets");
                   cmdGets(fd);
                   break;
               }
        case 6:{
                   writeIntoLog(logFd,username,"remove");
                   cmdRemove(fd);
                   break;
               }
        case 7:{
                   writeIntoLog(logFd,username,"pwd");
                   cmdPwd(fd);
                   break;
               }
        case 8:{
                   writeIntoLog(logFd,username,"mkdir");
                   cmdMkdir(fd);
                   break;
               }
        default:break;
        }
    }
    return 0;
}

int recvCycle(int sfd,void* buf,int recvLen){
    char *p=(char*)buf;
    int total=0,ret;
    while(total<recvLen)
    {
        ret=recv(sfd,p+total,recvLen-total,0);
        if(0==ret)
        {
            return -1;
        }
        total+=ret;
    }
    return 0;
}

int getNowTime(char *timeString){
    /*日志记录使用*/
    time_t timep;
    struct tm *pTm;
    time(&timep);
    pTm = gmtime(&timep);
    sprintf(timeString,"%04d-%02d-%02d\t%02d:%02d:%02d\t",
            (1900 + pTm->tm_year), (1 + pTm->tm_mon), (pTm->tm_mday),
            (8 + pTm->tm_hour), (pTm->tm_min), (pTm->tm_sec));
    return 0;
}

int writeIntoLog(int logFd,char *username,char *operation){
    char timeString[40]={0};
    char logString[100]={0};
    getNowTime(timeString);
    sprintf(logString,"%s\t%s\t%s\n",timeString,username,operation);
    printf("\nlogString=%s\n",logString);
    write(logFd,logString,strlen(logString));
    return 0;
}

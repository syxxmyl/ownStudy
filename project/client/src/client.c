#include "../include/client.h"

int confInit(char *confFilePath,int *socketFd){
    FILE *fd=fopen(confFilePath,"rb+");
    char ip[20]={0};
    int port;
    int ret=fscanf(fd,"ip=%s\nport=%d",ip,&port);
    printf("ip=%s,port=%d\n",ip,port);
    int sfd;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(port);
    serAddr.sin_addr.s_addr=inet_addr(ip);
    ret=connect(sfd,(struct sockaddr *)&serAddr,sizeof(serAddr));
    if(ret==-1){
        printf("服务器端未开放\n");
        exit(0);
    }
    *socketFd=sfd;
    fclose(fd);
    return 0;
}

int userLogin(int socketFd){
    char username[20]={0};
    char *password;
    train_t train;
    char loginFlag=0;
    while(1){
        bzero(&username,20);
        printf("请输入用户名:\n");
        scanf("%s",username);
        train.cmdType=0;//0表示传递的是用户名
        train.datalen=strlen(username);
        strcpy(train.buf,username);
        send(socketFd,&train,train.datalen+8,0);

        password=getpass("请输入密码：");
        train.cmdType=1;//1表示传递的是密码
        train.datalen=strlen(password);
        strcpy(train.buf,password);
        send(socketFd,&train,train.datalen+8,0);

        recvCycle(socketFd,&loginFlag,1);
        if(loginFlag==1){
            printf("登录成功\n");
            break;
        }else{
            printf("登录失败，请重新输入\n");
        }
    }
    return 0;
}

int divideBuf(char *buf,char *cmd,char *args){
    int i=0,j=0;
    int flag=0;
    int t=0;
    while(buf[i]!=0){
        if(buf[i]==' '){
            strncpy(cmd,buf,j);
            flag=1;
            t=j+1;
            j=0;
        }else{
            j++;
        }
        i++;
    }
    if(flag==0){
        strncpy(cmd,buf,j);
    }else{
        strncpy(args,buf+t,j);
    }
    return 0;
}

int sendClientRequest(int socketFd){
    char cmd[100]={0};
    char args[100]={0};
    char dir[100]={0};
    char buf[100]={0};
    int times=0;
    while(1){
        bzero(&buf,sizeof(buf));
        bzero(&cmd,sizeof(cmd));
        bzero(&args,sizeof(args));
        bzero(&dir,sizeof(dir));
        if(times){
            cmdPwd(socketFd,dir);
            if(strlen(dir)==0){
                printf("服务器端断开连接\n");
                exit(0);
            }
            printf("%s>",dir);
            fflush(stdout);
            bzero(&dir,sizeof(dir));
        }
        gets(buf);
        divideBuf(buf,cmd,args);
        if(strcmp(cmd,"pwd")==0){//7
            cmdPwd(socketFd,dir);
            printf("%s\n",dir);
        }    
        else if(strcmp(cmd,"cd")==0){//2
            cmdCd(socketFd,args);
        }
        else if(strcmp(cmd,"ls")==0){//3
            cmdLs(socketFd);
        }
        else if(strcmp(cmd,"mkdir")==0){//8
            cmdMkdir(socketFd,args);
        }
        else if(strcmp(cmd,"remove")==0){//6
            cmdRemove(socketFd,args);
        }
        else if(strcmp(cmd,"puts")==0){//4
            cmdPuts(socketFd,args);
        }
        else if(strcmp(cmd,"gets")==0){//5
            cmdGets(socketFd,args);
        }
        else if(strcmp(cmd,"help")==0){
            printf("cd dir 进入目录\n");
            printf("ls 列出当前目录下文件信息\n");
            printf("puts file 将文件上传到服务器\n");
            printf("gets file 从服务器端下载文件到本地\n");
            printf("remove file 删除服务器上的文件\n");
            printf("pwd 显示当前所在路径\n");
            printf("mkdir dir 创建新的目录\n");
        }else{
            if(times==0){
                times=1;
                continue;
            }
            printf("目前暂不支持%s命令\n",cmd);
        }
    }
    return 0;
}

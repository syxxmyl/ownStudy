#define _GNU_SOURCE
#include "../include/cmd.h"

int cmdCd(int fd,char *preDir){
    train_t train;
    recvCycle(fd,&train.datalen,sizeof(int));
    char buf[100]={0};
    recvCycle(fd,&buf,train.datalen);
    char dir[100]={0};
    sprintf(dir,"%s%c%s",getcwd(NULL,0),'/',buf);
    /*切换工作路径*/
    int ret=chdir(dir);
    bzero(&dir,sizeof(dir));
    strcpy(dir,getcwd(NULL,0));//切换后的工作路径
    if(strcmp(dir,preDir)<0){
        chdir(preDir);
        printf("试图越界访问目录\n");
        bzero(&dir,sizeof(dir));
        strcpy(dir,preDir);
    }
    char flag=0;
    if(ret==-1){
        send(fd,&flag,1,0);
        return 0;
    }else{
        flag=1;
        send(fd,&flag,1,0);
    }
    bzero(&train,sizeof(train));
    train.cmdType=2;
    train.datalen=strlen(dir);
    strcpy(train.buf,dir);
    send(fd,&train,train.datalen+8,0);
    return 0;
}

void showPrivilege(int num,char *res){
    int i;
    if(num>=32768){
        res[0]='-';

    }else{
        res[0]='d';
    }
    for(i=0;i<9;i++){
        if((num&1)==1){
            if(i%3==0){
                res[9-i]='x';
            }else if(i%3==1){
                res[9-i]='w';
            }else{
                res[9-i]='r';
            }
        }else{
            res[9-i]='-'; 
        }
        num=num>>1;
    }
    res[10]='\0';
}

void show_ls(char *fileName, char *outbuf){
    DIR *pDir;
    struct dirent *pDirent;
    struct stat fileStatBuf;/*文件状态*/
    char infomation[1000];
    char buf[300];/*设置小了gcc会警告*/
    pDir = opendir(fileName);/*获取目录下的所由文件和目录的列表*/
    if (NULL == pDir) {
        printf( "ls: can not read \n" );
    }
    while((pDirent = readdir(pDir)) != NULL) { /*遍历读取 opendir 返回值的那个列表*/
        if(strcmp(pDirent->d_name,".")==0||strcmp(pDirent->d_name,"..")==0){
            continue;                    
        }
        bzero(&fileStatBuf, sizeof(struct stat));
        stat(pDirent->d_name, &fileStatBuf);
        mode_t mode = fileStatBuf.st_mode;
        if (S_ISREG(mode)){/*普通文件*/
            sprintf(infomation, "- ");
        }else if(S_ISDIR(mode)){/*目录文件*/
            sprintf(infomation, "d ");                    
        }
        sprintf(buf, " %10ldB  %s\n" ,fileStatBuf.st_size, pDirent->d_name);
        strcat(infomation,buf);
        strcat(outbuf,infomation);
    }
    closedir(pDir);
}

int cmdLs(int fd){
    train_t train;
    bzero(&train,sizeof(train));
    char buf[1000]={0};
    show_ls(".", buf);
    train.cmdType=3;
    train.datalen=strlen(buf);
    strcpy(train.buf,buf);
    send(fd,&train,train.datalen+8,0);
    return 0;
}

int cmdPwd(int fd){
    char dir[100]={0};
    strcpy(dir,getcwd(NULL,0));
    printf("dir = %s\n",dir);
    train_t train;
    train.cmdType=7;
    train.datalen=strlen(dir);
    strcpy(train.buf,dir);
    send(fd,&train,train.datalen+8,0);
    return 0;
}

int cmdMkdir(int fd){
    train_t train;
    bzero(&train,sizeof(train));
    recvCycle(fd,&train.datalen,4);
    recvCycle(fd,train.buf,train.datalen);
    printf("buf=%s\n",train.buf);
    mkdir(train.buf,0775);
    return 0;
}

/*递归删除目录(删除该目录以及该目录包含的文件和目录)*/
int remove_dir(char *dir){
    char cur_dir[] = ".";
    char up_dir[] = "..";
    char dir_name[260];/*小于257 GCC 会警告*/
    DIR *dirp;
    struct dirent *dp;
    struct stat dir_stat;
    /*参数传递进来的目录不存在，直接返回*/
    if (0 != access(dir, F_OK)) {
        return 0;
    }
    /*获取目录属性失败，返回错误*/
    if (0 > stat(dir, &dir_stat)){
        perror("get directory stat error");
        return -1;
    }
    if (S_ISREG(dir_stat.st_mode)) {/*普通文件直接删除*/
        remove(dir);
    } else if (S_ISDIR(dir_stat.st_mode)) { /*目录文件，递归删除目录中内容*/
        dirp = opendir(dir);
        while((dp = readdir(dirp)) != NULL) {
            /* 忽略 . 和 ..*/
            if ((0 == strcmp(cur_dir, dp->d_name)) || (0 == strcmp(up_dir, dp->d_name))) {
                continue;
            } 
            sprintf(dir_name, "%s/%s", dir, dp->d_name);
            remove_dir(dir_name);   /*递归*/
        }
        closedir(dirp);
        rmdir(dir);/*删除空目录*/
    } else {
        perror("unknow file type!"); 
    }
    return 0;
}

int cmdRemove(int fd){
    train_t train;
    bzero(&train,sizeof(train));
    recvCycle(fd,&train.datalen,4);
    recvCycle(fd,train.buf,train.datalen);
    printf("buf=%s\n",train.buf);
    remove_dir(train.buf);
    return 0;
}

int cmdPuts(int newFd)
{
    train_t train;
    char buf[1000]={0};
    memset(buf,0,sizeof(buf));
    int ret;
    char flag;
    ret=recvCycle(newFd,&flag,1);
    if(flag==0){
        printf("试图发送不存在的文件\n");
        return 0;
    }
    //接收文件名
    recvCycle(newFd,&train.cmdType,4); 
    recvCycle(newFd,&train.datalen,4);
    recvCycle(newFd,buf,train.datalen);
    bzero(&train,sizeof(train));
    int fd=open(buf,O_CREAT|O_RDWR,0666);
    printf("recv file fd=%d\n",fd);
    off_t fileSize,downLoadSize=0;
    //接收文件大小
    recvCycle(newFd,&train.cmdType,4);
    recvCycle(newFd,&train.datalen,4);
    recvCycle(newFd,&fileSize,train.datalen);//fileSize是文件
    printf("filename=%s,filesize=%ld\n",buf,fileSize);
    int fds[2];
    pipe(fds);
    while(downLoadSize<fileSize)
    {
        //如果是65536会把客户端在client.c里传递的cmdType=7请求当前目录给吃掉
        ret=splice(newFd,NULL,fds[1],NULL,fileSize-downLoadSize,SPLICE_F_MOVE|SPLICE_F_MORE);
        splice(fds[0],NULL,fd,NULL,ret,SPLICE_F_MOVE|SPLICE_F_MORE);
        downLoadSize+=ret; 
    }
    printf("上传成功,downLoadSize=%ld\n",downLoadSize);
    close(fds[0]);
    close(fds[1]);
    close(fd);
    return 0;
}

int cmdGets(int fd){
    //接收文件名
    train_t train;
    bzero(&train,sizeof(train));
    recvCycle(fd,&train.datalen,4);
    recvCycle(fd,&train.buf,train.datalen);
    char fileName[100]={0};
    strcpy(fileName,train.buf);
    printf("fileName=%s\n",fileName);
    //判断当前路径下是否有该文件，没有的话就传输0表示错误
    int fileFd=open(fileName,O_RDWR);
    char flag=0;
    if(fileFd==-1){
        send(fd,&flag,1,0);
        printf("当前路径不存在该文件\n");
        return 0;
    }else{
        flag=1;
        send(fd,&flag,1,0);
        //断点续传位置，接收对方发送的已下载的字节数，偏移后再传输
        off_t finishDownLoadSize=0;
        recvCycle(fd,&train.cmdType,4); 
        recvCycle(fd,&train.datalen,4);
        recvCycle(fd,&finishDownLoadSize,train.datalen);
        //传输文件大小
        off_t needDownLoadSize=0;
        bzero(&train,sizeof(train));
        train.cmdType=5;
        struct stat file;
        fstat(fileFd,&file);
        lseek(fileFd,finishDownLoadSize,SEEK_SET);
        train.datalen=sizeof(file.st_size);
        needDownLoadSize=file.st_size-finishDownLoadSize;
        memcpy(train.buf,&needDownLoadSize,train.datalen);
        send(fd,&train,train.datalen+8,0);
        printf("fileSize=%ld,needDownLoadSize=%ld\n",file.st_size,needDownLoadSize);
        //传输文件内容
        off_t changeFunc=1024*1024*100;
        int ret;
        if(changeFunc<=needDownLoadSize){
            printf("使用mmap\n");
            char *pMap=(char*)mmap(NULL,needDownLoadSize,PROT_READ|PROT_WRITE,MAP_SHARED,fileFd,0);
            ERROR_CHECK(pMap,(char*)-1,"mmap");
            ret=send(fd,pMap,needDownLoadSize,0);
        }else{
            ret=sendfile(fd,fileFd,NULL,needDownLoadSize); 
        }
        printf("sendfile ret=%d\n",ret);
    }
    return 0;
}

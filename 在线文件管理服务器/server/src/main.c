#include "../include/init.h"
#include "../include/fd_pass.h"

int exitFds[2];

void sigExitFunc(int sigNum)
{
    write(exitFds[1],&sigNum,1);
}

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int socketFd;
    int processNum;
    confInit(argv[1],&socketFd,&processNum);
    printf("socketFd=%d,processNum=%d\n",socketFd,processNum);
    pProcessData_t processInfo;
    processInfo=(pProcessData_t)calloc(processNum,sizeof(processData_t));
    processPoolInit(processInfo,processNum);
    pipe(exitFds);
    signal(SIGUSR1,sigExitFunc);
    int i;
    for(i=0;i<processNum;i++){
        printf("pid=%d,pipeFd=%d,busy=%d\n",processInfo[i].pid,processInfo[i].pipeFd,processInfo[i].busy);
    }
    int epollFd=epoll_create(1);
    epollAdd(epollFd,socketFd);
    epollAdd(epollFd,exitFds[0]);
    for(i=0;i<processNum;i++){
        epollAdd(epollFd,processInfo[i].pipeFd);
    }
    struct epoll_event *evs;
    evs=(struct epoll_event*)calloc(processNum+2,sizeof(struct epoll_event));
    int readyFdCount,newFd,j;
    char noBusyFlag;
    pid_t pid;
    int status;
    while(1){
        readyFdCount=epoll_wait(epollFd,evs,processNum+2,-1);
        for(i=0;i<readyFdCount;i++){
            if(evs[i].data.fd==exitFds[0]){
                for(j=0;j<processNum;j++)
                {
                    sendFd(processInfo[j].pipeFd,0,1);
                }
                for(j=0;j<processNum;j++)
                {
                    pid=wait(&status);
                    if(WIFEXITED(status))
                    {
                        printf("%d exit code is %d\n",pid,WEXITSTATUS(status));
                    }
                }
                printf("exit ok\n");
                exit(0);
            }

            if(evs[i].data.fd==socketFd){
                newFd=accept(socketFd,NULL,NULL);
                for(j=0;j<processNum;j++){
                    if(processInfo[j].busy==0){
                        sendFd(processInfo[j].pipeFd,newFd,0); 
                        processInfo[j].busy=1;
                        printf("%d is busy\n",processInfo[j].pid);
                        break;
                    }
                }
                close(newFd);
            }

            for(j=0;j<processNum;j++){
                if(evs[i].data.fd==processInfo[j].pipeFd){
                    read(processInfo[j].pipeFd,&noBusyFlag,1);
                    processInfo[j].busy=0;
                    printf("%d is not busy\n",processInfo[j].pid);
                    break;
                }
            }
        }
    }
    return 0;
}


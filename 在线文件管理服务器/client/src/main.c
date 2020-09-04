#include "../include/client.h"

int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);

    int socketFd;
    confInit(argv[1],&socketFd);

    userLogin(socketFd);

    sendClientRequest(socketFd);


    return 0;
}

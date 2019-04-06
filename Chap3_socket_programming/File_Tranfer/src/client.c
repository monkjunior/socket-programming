#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>

#define SERVERPORT 8888

int main(){
    int sock2;
    struct sockaddr_in sock2_addr, sock1_addr;
    int returnStatus;

    sock2 = socket(AF_INET, SOCK_STREAM, 0);
    if (sock2 == -1){
        printf("Can not create client socket!\n");
        return -1;
    }
    printf("Created a client socket.\n");

    bzero(&sock1_addr, sizeof(sock1_addr));
    sock1_addr.sin_family = AF_INET;
    sock1_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock1_addr.sin_port = htons(SERVERPORT);

    returnStatus = connect(sock2, (struct sockaddr*)&sock1_addr, sizeof(sock1_addr));
    if (returnStatus == -1){
        printf("Can not connect to server.\n");
        return -1;
    }
    else{
        printf("Connected to server.\n");
    }

    return 0;
}
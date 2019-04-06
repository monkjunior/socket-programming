/*Watch out the fctl.h - file control options*/
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>

#define SERVERPORT 8888
#define MAXBUF 1024

int main(){
    /*Initialize 2 sockets: sock1-server, sock2-client*/
    int sock1, sock2;
    struct sockaddr_in sock1_addr, sock2_addr;
    int sock2_addr_length;
    int returnStatus;

    sock1 = socket(AF_INET, SOCK_STREAM, 0);
    if(sock1 == -1){
        printf("Can not create server socket!\n");
        return -1;
    }

    bzero(&sock1_addr, sizeof(sock1_addr));
    sock1_addr.sin_family = AF_INET;
    sock1_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock1_addr.sin_port = htons(SERVERPORT);

    returnStatus = bind(sock1, (struct sockaddr*)&sock1_addr, sizeof(sock1_addr));
    if (returnStatus == -1){
        printf("Could not bind to server address!\n");
        return -1;
    }
    printf("Bind completely!\n");

    while (1){
        returnStatus = listen(sock1, 5);
        if (returnStatus == -1){
            printf("Can not listen for connections!\n");
            return -1;
        }
        
        else{
            sock2_addr_length = sizeof(sock2_addr);
            sock2 = accept(sock1, (struct sockaddr*)&sock2_addr, &sock2_addr_length);
            if (sock2 == -1){
                printf("Can not accept client!\n");
                return -1;
            }
            else{
                printf("Connected to client!\n");
                /*Start tranffering file*/
            }
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#define MAXBUF 1024

/*   Run ./main <server_port>   */
int main(int argc, char *argv[]){
    int returnStatus;
    int server_socket;
    int server_port;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int client_addr_length;
    char buf[MAXBUF];

    if(argc != 2){
        printf("Wrong input!\n");
        return -1;
    }
    
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1){
        printf("Can not creat socket!\n");
        return -1;
    }
    printf("Server socket was created.\n");

    server_port = atoi(argv[1]);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    returnStatus = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(returnStatus == 0){
        printf("Bind completed!\n");
    }
    else{
        printf("Can not bind to server socket address!\n");
        return -1;
    }

    client_addr_length = sizeof(client_addr);
    while(1){
        returnStatus = recvfrom(server_socket, buf, MAXBUF, 0, (struct sockaddr*)&client_addr, &client_addr_length);
        if (returnStatus == -1){
            printf("Could not receive message!\n");
            /*Dont return here because UDP is not a reality protocol*/
        }
        else{
            printf("Client: %s\n", buf);
            strcpy(buf, "OK");
            returnStatus = sendto(server_socket, buf, strlen(buf)+1, 0, (struct sockaddr*)&client_addr, client_addr_length);
            if (returnStatus == -1){
                printf("Server: MISSED\n");
            }
            else{
                printf("Server: OK\n");
            }
        }
    }
    return 0;
}
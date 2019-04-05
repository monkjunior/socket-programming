#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>

#define MAXBUF 1024

/* Run ./main <local_addr> <server_port> */
int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Wrong input!\n");
        return -1;
    }

    int client_socket;
    int server_port;
    struct sockaddr_in client_addr, server_addr;
    int server_addr_length;
    char buf[MAXBUF];
    int returnStatus;

    /*Create and setup client socket*/
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1){
        printf("Can not created a socket for client!\n");
        return -1;
    }
    printf("Created a client's socket!\n");

    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    client_addr.sin_port = 0;

    returnStatus = bind(client_socket, (struct sockaddr *)&client_addr, sizeof(client_addr));
    if (returnStatus == -1){
        printf("Can not bind to client's address!\n");
        return -1;
    }

    /*Setup server address and mechanism to send-receive message*/
    server_port = atoi(argv[2]);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;   
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(server_port    );
    printf("Set up server on port %d!\n", server_port);

    while(1){
        printf("Client: ");
        gets(buf);
        returnStatus = sendto(client_socket, buf, strlen(buf)+1, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
        if (returnStatus == -1){
            printf("Could not send message to server!\n");
            /*Dont return to end here because this is UDP*/
        }
        else{
            server_addr_length = sizeof(server_addr);
            returnStatus = recvfrom(client_socket, buf, MAXBUF, 0, (struct sockaddr*)&server_addr, &server_addr_length);
            if (returnStatus == -1){
                printf("Server: MISSED\n");
            }
            else
            {
                printf("Server: %s\n", buf);
            }
            
        }
    }

    close(client_socket);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>

int main(){
    int clientSocket;
    struct sockaddr_in simpleServer;
    int returnStatus;

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == -1){
        printf("Unsuccessfull creating client socket!\n");
        return -1;
    }

    printf("Client socket = %d\n", clientSocket);

    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
    simpleServer.sin_port = htons(8000);

    returnStatus = connect(clientSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

    if (returnStatus == 0){
        printf("Connect successfully!\n");
    }
    else{
        printf("Can not connect to server socket!\n");
        close(clientSocket);
        return-1;
    }

    return 0;
}
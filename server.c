#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>

const char MESSAGE[] = "Hello, my name is SOCKET!\n";

int main(){
   int server_socket;
   struct sockaddr_in simpleServer;
   int returnStatus;

   server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if (server_socket == -1){
    printf("Unsuccessfull creating server socket!\n");
    return -1;
   } 
   printf("Server socket = %d\n", server_socket);

   simpleServer.sin_family = AF_INET;
   simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
   simpleServer.sin_port = htons(8000);

   returnStatus = bind(server_socket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));
   if (returnStatus == 0){
       printf("Bind completerd!\n");
   }
   else{
       printf("Bind unsuccessfully, exit!\n");
       close(server_socket);
       return -1;
   }

   returnStatus = listen(server_socket, 5);
   if (returnStatus == -1){
       printf("Can not listen to the socket!\n");
       close(server_socket);
       return -1;
   }
   printf("Server is listening on port %d!\n", simpleServer.sin_port);
   
   while(1){
    /*Set up variables to handle client connect*/
    struct sockaddr_in clientName = {0};
    int simpleClient;
    int clientNameLength = sizeof(clientName);

    /*Block on accecpt function call*/
    simpleClient = accept(server_socket, (struct sockaddr *)&clientName, &clientNameLength);

    if (simpleClient == -1){
        printf("Cannot accept connection!\n");
        close(server_socket);
        return -1;
    }
    
    printf("Accepted connection!\n");
    write(simpleClient, MESSAGE, strlen(MESSAGE));
    close(simpleClient);
    break;
   }

   close(server_socket);
   return 0;    
}
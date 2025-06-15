#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define PORT 6000
#define BUFFER_SIZE 1024
int main(){
    int client_socket;
    int server_socket;
    struct sockaddr_in address;
    socklen_t addr_len = sizeof(address);
    char buffer[BUFFER_SIZE];
    server_socket = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    bind(server_socket,(struct sockaddr*)&address,addr_len);
    listen(server_socket,10);
    printf("Server is Listening to Port %d\n",PORT);
    client_socket = accept(server_socket,(struct sockaddr*)&address,&addr_len);
    printf("Connected to the Client\n");
    while(1){
        int bytes = recv(client_socket,buffer,BUFFER_SIZE,0);
        if(bytes<=0){
            printf("Connection Broke\n");
            break;
        }
        printf("Client : %s\n",buffer);
        memset(buffer,0,BUFFER_SIZE);
        printf("You : ");
        scanf("%[^\n]*c",buffer);
        send(client_socket,buffer,strlen(buffer),0);
    }
    close(client_socket);
    close(server_socket);
    return 0;
}
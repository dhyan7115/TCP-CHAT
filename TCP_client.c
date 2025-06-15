#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define PORT 6000
#define BUFFER_SIZE 1024
int main(){
    int sock;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(address);
    sock = socket(AF_INET,SOCK_STREAM,0);
    address.sin_port = htons(PORT);
    address.sin_family = AF_INET;
    if(inet_pton(AF_INET,"127.0.0.1",&address.sin_addr)<=0){
        printf("Invalid IP\n");
        exit(1);
    }
    if(connect(sock,(struct sockaddr*)&address,addr_len)<0){
        printf("Connection Failed\n");
        exit(1);
    }
    printf("Connection Established with the Server\n");
    while(1){
        printf("You : ");
        fgets(buffer,BUFFER_SIZE,stdin);
        send(sock,buffer,strlen(buffer),0);
        memset(buffer,0,BUFFER_SIZE);
        int bytes = recv(sock,buffer,BUFFER_SIZE,0);
        if(bytes<=0){
            printf("Connection Failed\n");
            break;
        }
        printf("Server : %s\n",buffer);
    }
    close(sock);
    return 0;
}
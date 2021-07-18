#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 5000
struct sockaddr_in clientaddr;
void chat(int sockfd){
    while(1){
        char buffer[200];
        struct sockaddr_in servaddr;
        printf("Client: ");
        scanf("%[^\n]%*c", buffer);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &clientaddr,sizeof(clientaddr));
        strcpy(buffer,"");
        int n=recvfrom(sockfd, buffer, sizeof(buffer), MSG_WAITALL, ( struct sockaddr *)NULL,NULL);
        buffer[n]='\0';
        printf("Server: %s [MSG LENGTH: %d]\n",buffer,strlen(buffer));
        strcpy(buffer,"");
    }
}
int main() {
    
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);   
    if(sockfd==-1){
        printf("Socket creation failed\n");
        exit(1);
    }
    printf("Socket created successfully\n");
    clientaddr.sin_family=AF_INET;
    clientaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    clientaddr.sin_port=htons(PORT);
    chat(sockfd);
}
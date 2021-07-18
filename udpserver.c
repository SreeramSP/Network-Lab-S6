#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 5000
struct sockaddr_in servaddr;
void chat(int sockfd){
    while(1){
        char buffer[200];
        struct sockaddr_in cliaddr;
        int len=sizeof(cliaddr);
        int n=recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, ( struct sockaddr *)&cliaddr,&len);
        buffer[n]='\0';
        printf("Client: %s [MSG LENGTH: %d]\n",buffer,strlen(buffer));
        printf("Server: ");
        scanf("%[^\n]%*c", buffer);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &cliaddr,sizeof(cliaddr));
        strcpy(buffer,"");
    }
}
int main(){
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);   
    if(sockfd==-1){
        printf("Socket creation failed\n");
        exit(1);
    }
    printf("Socket created successfully\n");
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(PORT);
    if((bind(sockfd,( struct sockaddr *)&servaddr,sizeof(servaddr)))==-1)
    {
        printf("Failed to bind socket with IP and port\n");
        exit(0);
    }
    printf("Socket bind was successful\n");
    chat(sockfd);
}
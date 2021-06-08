#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define PORT 8080
#define SA struct sockaddr
void chat(sockfd)
{
    char buff[80];
    while(1)
    {
        strcpy(buff,"\n");
        printf("Client: ");
        scanf("%[^\n]%*c", buff);
        if(strcmp(buff,"exit")==0)
        {
            printf("EXIT command detected\n");
            exit(0);
        }
        write(sockfd,buff,sizeof(buff));
        strcpy(buff,"\n");
        read(sockfd,buff,sizeof(buff));
        printf("Server: %s [MSG LENGTH:%d]\n",buff,strlen(buff));
    }
}
int main()
{
    int sockfd,connfd;
    struct sockaddr_in servaddr, cli;
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1)
    {
        printf("Socket could not be created\n");
        exit(0);
    }
    printf("Socket created successfully\n");
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servaddr.sin_port=htons(PORT);
    if(connect(sockfd,(SA*)&servaddr,sizeof(servaddr))==-1)
    {
        printf("Connection with server was unsuccessful. Server could be offline\n");
        exit(0);
    }
    printf("Connected successfully to server\n\n\n");
    chat(sockfd);
    close(sockfd);
    return 0;
}
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORT 8080
#define SA struct sockaddr
void chat(int sockfd)
{
    char buff[80];
    int n;
    while(1)
    {
        strcpy(buff,"\n");
        read(sockfd,buff,sizeof(buff));
        printf("Client: %s [MSG LENGTH:%d]\n",buff,strlen(buff));
        strcpy(buff,"\n");
        printf("Server: ");
        scanf("%[^\n]%*c", buff);
        if(strcmp(buff,"exit")==0)
        {
            printf("EXIT command detected\n");
            exit(0);
        }
        write(sockfd,buff,sizeof(buff));
    }
    
}
int main()
{
    int sockfd,connfd,len;
    struct sockaddr_in servaddr, cli;
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1)
    {
        printf("Socket could not be created\n");
        exit(0);
    }
    printf("Socket created successfully\n");
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(PORT);
    if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr)))==-1)
    {
        printf("Failed to bind socket with IP and port\n");
        exit(0);
    }
    printf("Socket bind was successful\n");
    if((listen(sockfd,5))!=0)
    {
        printf("Listen failed\n");
        exit(0);
    }
    printf("Server is listening\n\n\n");
    len=sizeof(cli);
    connfd=accept(sockfd, (SA*)&cli,&len);
    if(connfd==-1)
    {
        printf("Server accept failed\n");
        exit(0);
    }
    printf("Server is accepting data\n");
    chat(connfd);
    close(sockfd);
    return 0;
}
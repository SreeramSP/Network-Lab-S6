#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
struct msg_queue{
    long msg_type;
    char msg_text[100];
}message;
void main(){
    int key,msg_id;
    key=ftok("progfile",65);
    msg_id=msgget(key, 0666|IPC_CREAT);
    if(msg_id<0){
        printf("Message queue could not  be created");
        exit(1);
    }
    msgrcv(msg_id,&message,sizeof(message),1,0);
    printf("Message received:  %s\n",message.msg_text);
    msgctl(msg_id,IPC_RMID,NULL);
}
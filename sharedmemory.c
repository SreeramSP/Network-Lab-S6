#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
void main(){
    int key=ftok("shmfile",65);
    int shmid=shmget(key,1024,0666|IPC_CREAT);
    int *shmptr=shmat(shmid,NULL,0);
    int num;
    int f=fork();
    if(f==1){
        printf("Fork creation failed\n");
        exit(1);
    }
    else if(f>0){ //Parent process
        wait();
        int val=*shmptr;
        int square=val*val;
        printf("The square of %d is %d\n",*shmptr,square);
        
    }
    else{//Child process
        printf("Enter a number: ");
        scanf("%d",&num);
        *shmptr=num;
    }
    shmdt(shmptr);
    shmctl(shmid,IPC_RMID,NULL);
}
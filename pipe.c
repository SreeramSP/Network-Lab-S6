#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
    int pipe1[2], pipe2[2];
    int pid,status1,status2;
    char pipe1_read[50],pipe1_write[50],pipe2_read[50],pipe2_write[50];
    char new[50]="Hello";
    status1=pipe(pipe1);
    status2=pipe(pipe2);
    if((status1==-1)||(status2==-1))
    {
        printf("pipe creation failed");
    }
    pid=fork();
    if(pid>0) //parent process
    {
      
        printf("1st parent process\n");
        printf("Enter the data =");
        scanf("%s",pipe1_write);
        write(pipe1[1],pipe1_write,50);
        wait(NULL);
        //2nd pipe reading the data
        read(pipe2[0],pipe2_read,50);
        printf("The data concatinated is %s",pipe2_read);

    }
    if(pid==0) //child process
    { 
         read(pipe1[0],pipe1_read,30);
         int i;
         int k=strlen(new);
         for(i=0;i<strlen(pipe1_read);i++)
         new[k++]=pipe1_read[i];
         new[k]='\0';
         //sending concatinated string to pipe2
         write(pipe2[1],new,50);

    }
    
}
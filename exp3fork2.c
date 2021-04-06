#include <stdio.h>
#include <unistd.h>
int main()
{
        int x;
        x= fork();
        if(x==0)
        {
                printf("C2, PID =%d Parent= %d\n ",getpid(), getppid());
        }
        else if(x>0)
        {
                printf("P, PID =%d\n", getpid());
                x= fork();
                if(x==0)
                {
                        printf("C1 , PID =%d Parent = %d\n", getpid(), getppid());
                        x= fork();
                        if(x==0)
                        {
                                printf("C3 , PID =%d Parent = %d\n", getpid(), getppid());
                        }
                }
        }
}        
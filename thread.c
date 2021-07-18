#include<stdio.h>
#include<pthread.h>
int limit;
void *fib(void *var){
    int a=0,b=1,c=1,n=0;
    while(n!=limit){
        printf("%d\n",a);
        a=b;
        b=c;
        c=a+b;
        n++;
    }
}
void *prime(void *var){
    int factors=0;
    for(int i=1;i<=limit;i++){
        if(limit%i==0){
            factors++;
        }
    }
    if(factors==2)
        printf("%d IS PRIME\n",limit);
    else
        printf("%d IS NOT PRIME\n",limit);
}
void main(){
    pthread_t thread1, thread2;
    printf("Enter the limit: ");
    scanf("%d",&limit);
    pthread_create(&thread1, NULL, fib, NULL);
    pthread_create(&thread2, NULL, prime, NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_exit(NULL);
}
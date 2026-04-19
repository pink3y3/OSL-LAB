#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int fib[50],n;

void *fibonacci(void *arg){
    fib[0]=0;
    fib[1]=1;
    for(int i=2;i<n;i++){
        fib[i]=fib[i-1]+fib[i-2];
    }
    pthread_exit(NULL);
}

int main(){
    printf("enter number of fibonacci numbers to be generated: ");
    scanf("%d",&n);
    pthread_t t1;
    pthread_create(&t1,0,fibonacci,0);
    pthread_join(t1,NULL);
    printf("fibonacci series: ");
    for(int i=0;i<n;i++){
        printf("%d ",fib[i]);
    }
    printf("\n");
    return 0;
}
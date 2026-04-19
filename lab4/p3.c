//wait process
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

void main(){
    int status;
    pid_t pid;
    pid=fork();

    if(pid==-1){
        printf("ERROR: child not created");
    }

    else if(pid==0){
        printf("i am the child");
        exit(0);
    }
    else{
        wait(&status);
        printf("\ni'm the parent");
        printf("\nchild returned: %d\n",status);
    }
}
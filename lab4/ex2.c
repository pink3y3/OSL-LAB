#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
    pid_t pid;
    pid=fork();
    if(pid<0){
        printf("error");
        exit(1);
    }
    else if(pid==0){
        execl("./ex1","ex1",NULL);
    }
    else{
        wait(NULL);
        printf("\nparent process executing");
        printf("\nchild process executed");
        exit(1);
    }
}
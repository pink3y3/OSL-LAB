#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    pid_t pid;
    pid=fork();
    if(pid<0){
        printf("\nchild process not created\n");
        exit(1);
    }
    else if(pid==0){
        printf("\nchild process created...\n");
        printf("\npid of child process: %d",getpid());
        printf("\nppid of child process: %d",getppid());
    }
    else{
        wait(NULL);
        printf("\nparent process running\n");
        printf("\npid of parent process: %d",getpid());
        printf("\nppid of parent process: %d",getppid());
        printf("\nchild process executed\n");
        exit(0);
    }
}
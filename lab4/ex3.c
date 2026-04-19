#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    pid_t pid;
    pid=fork();
    if(pid<0){
        printf("error");
        exit(1);
    }
    else if(pid==0){
        printf("\nchild process");
        printf("\npid: %d",getpid());
        printf("\nppid: %d",getppid());
        exit(0); //child terminates immediately
    }
    else{
        printf("\nparent process is sleeping\n");
        sleep(20); //child is a zombie for 20 seconds
        printf("\nparent process is terminating\n");
    }
    return 0;
}
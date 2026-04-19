//forking a separate process using execlp ( no need to specify entire path of function)
//lp- path is included in command so no need to specify. -> significance of p
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
    pid_t pid;
    pid=fork();
    if(pid<0){
        printf("fork failed");
        exit(-1);
    }
    else if(pid==0){
        execlp("ls","ls",NULL);
    }
    else{
        wait(NULL);
        printf("child is complete");
        exit(0);
    }
}
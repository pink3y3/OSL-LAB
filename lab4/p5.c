//forking a new process with execl ( need to specify the entire path for l)

#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
    pid_t pid;
    pid=fork();
    if(pid<0){
        printf("error");
        exit(-1);
    }
    else if(pid==0){
        execl("/usr/bin/wc","wc","-l","foo.txt",NULL);
    }
    else{
        wait(NULL);
        printf("child is complete\n");
        exit(0);
    }
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    pid_t pid=fork();

    if(pid<0){
        printf("error");
        exit(1);
    }

    else if(pid==0){
        printf("child process\n");
        printf("pid of child: %d\n",getpid());
        printf("pid of parent before sleep: %d\n",getppid());

        sleep(5);

        printf("pid of parent after child exits: %d\n",getppid());
        printf("child exiting now..\n");
        exit(0);
    }

    else{
        printf("pid of parent: %d\n",getpid());
        printf("parent exiting now...\n");
        exit(0);
    }
    return 0;
}
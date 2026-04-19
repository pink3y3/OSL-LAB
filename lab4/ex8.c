#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    pid_t pid=fork();
    int status;

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
        printf("child exiting now with code 7\n");
        exit(7);
    }

    else{
        printf("pid of parent: %d\n",getpid());
        printf("parent waiting for child to terminate...\n");
        
        wait(&status);

        printf("child terminated\n");

        if(WIFEXITED(status)){
            printf("child exit code (leftmost byte of status): %d\n",WEXITSTATUS(status));
        }
    }
    return 0;
}
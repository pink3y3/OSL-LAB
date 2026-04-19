//fork execution

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid;
    char *message;
    printf("\nfork program starting");
    int n;
    pid=fork();
    switch(pid){
        case -1:
            perror("\nwhat the fork! forking failed"); 
            exit(1);
        case 0:
            message="\ni'm the child";
            n=5;
            break;
        default:
            message="\ni'm the parent";
            n=3;
            break;
    }
    for(;n>0;n--){
        puts(message);
        sleep(1);
    }
    exit(0);
}

//does pid become -1,0,1 again n again?
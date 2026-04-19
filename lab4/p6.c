//forking with execv (execute a program using an array of arguments instead of a list)

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(){
    pid_t pid;
    pid=fork();
    if(pid<0){
        fprintf(stderr,"execv failed: %s\n",strerror(errno));
        exit(-1);
    }
    else if(pid==0){
        char *args[]={"grep","-l","-n","admin","/etc/passwd",NULL};
        execv("/usr/bin/grep",args);
    }
    else{
        wait(NULL);
        printf("child is complete");
        exit(0);
    }
}

//execvp same thing but path doesnt need to be specified
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main(){
    int fd[2];
    pid_t pid;

    char write_msg[]="hello from parent";
    char read_msg[100];

    if(pipe(fd)==-1){
        printf("pipe failed");
        exit(-1);
    }
    pid=fork();

    if(pid<0){
        printf("error");
        exit(-1);
    }
    else if(pid==0){
        close(fd[1]);

        read(fd[0],read_msg,sizeof(read_msg));
        printf("child received: %s\n",read_msg);
        close(fd[0]);
        exit(0);
    }
    else{
        close(fd[0]);

        write(fd[1],write_msg,strlen(write_msg)+1);
        printf("\nparent sent: %s\n",write_msg);
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}
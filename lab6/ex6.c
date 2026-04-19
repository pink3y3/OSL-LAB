#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

int main(){
    int fd[2];
    char write_msg[]="hello from child";
    char read_msg[100];

    pid_t pid;

    if(pipe(fd)<0){
        printf("Error");
        exit(-1);
    }

    pid=fork();
    if(pid<0){
        printf("error");
        exit(-1);
    }

    else if(pid==0){
        close(fd[0]);

        write(fd[1],write_msg,strlen(write_msg)+1);
        printf("message sent from child: %s\n",write_msg);
        close(fd[1]);
        exit(0);
    }

    else{
        close(fd[1]);
        read(fd[0],read_msg,sizeof(read_msg));
        printf("parent received: %s\n",read_msg);
        close(fd[0]);
        wait(NULL);
    }
    return 0;
}
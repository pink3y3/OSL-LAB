#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>

int main(){
    pid_t pid;
    pid=fork();
    if(pid<0){
        printf("error");
        exit(1);
    }
    else if(pid==0){
        time_t t= time(NULL);
        struct tm *tm_info=localtime(&t);

        int minute=tm_info->tm_min;
        printf("child: current minute: %d\n",minute);

        if(minute%2==1){
            exit(0);
        }
        else{
            exit(1);
        }
    }
    else{
        int status;
        wait(&status);
        printf("minute is %s\n",(status >> 8)==0?"odd":"even");
    }
    return 0;
}

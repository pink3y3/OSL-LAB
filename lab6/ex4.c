#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<string.h>

#define n 5
#define max_len 50

struct msg_buffer{
    char words[n][max_len];
    int flag;
};

int main(){
    key_t key;
    int shmid;
    struct msg_buffer *ptr;

    key=ftok("queue",65);
    shmid=shmget(key,sizeof(struct msg_buffer),0666 | IPC_CREAT);
    if(shmid<0){
        printf("error");
        exit(-1);
    }
    ptr=(struct msg_buffer*)shmat(shmid,NULL,0);
    ptr->flag=0;
    
    pid_t pid=fork();
    if(pid<0){
        printf("error");
        exit(1);
    }
    else if(pid==0){
        while(ptr->flag!=1);
        printf("\nchild received: ");
        for(int i=0;i<n;i++){
            printf("%s",ptr->words[i]);
        }
        ptr->flag=0;
        shmdt(ptr);
        exit(0);
    }
    else{
        printf("\nenter set of words");
        for(int i=0;i<n;i++){
            scanf("%s",ptr->words[i]);
        }
        ptr->flag=1;
        printf("\nparent sent the words: ");
        for(int i=0;i<n;i++){
            printf("%s",ptr->words[i]);
        }
        while(ptr->flag!=0);
        printf("\ncame back to parent");
        shmdt(ptr);
        shmctl(shmid,IPC_RMID,NULL);
        wait(NULL);
    }
    return 0;
}
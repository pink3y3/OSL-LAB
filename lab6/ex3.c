#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/wait.h>

struct shared_data{
    char ch;
    int flag;
    //flag=0->parent can write
    //flag=1->child can read
    //flag=2->child responded
};

int main(){
    struct shared_data *ptr;
    key_t key;
    int shmid;

    key=ftok("shmfile",65);

    shmid=shmget(key,sizeof(struct shared_data),0666|IPC_CREAT);

    ptr = (struct shared_data*)shmat(shmid,NULL,0);
    ptr->flag=0;
    
    pid_t pid;
    pid=fork();

    if(pid<0){
        printf("error");
        exit(1);
    }
    else if(pid==0){
        while(ptr->flag!=1);
        printf("\nchild received %c",ptr->ch);
        if((ptr->ch>='a' && ptr->ch<='z') ||
            (ptr->ch>='A' && ptr->ch<='Z')){
                ptr->ch=ptr->ch+1;
            }
            ptr->flag=2;
            exit(0);
    }
    else{
        char input;
        printf("\nenter alphabet: ");
        scanf("%c",&input);
        ptr->ch=input;
        ptr->flag=1;
        printf("\nparent wrote %c",ptr->ch);
        while(ptr->flag!=2);
        printf("\nparent received from child %c",ptr->ch);
        shmdt(ptr);
        shmctl(shmid,IPC_RMID,NULL);
        wait(NULL);
    }
    return 0;
}
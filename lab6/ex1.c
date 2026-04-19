#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>

struct msg_buffer{
    long messageType;
    int number;
};

int isPalindrome(int num){
    int original=num;
    int reversed=0,digit;

    while(num>0){
        digit=num%10;
        reversed=reversed*10+digit;
        num/=10;
    }
    return (original==reversed);
}

int main(){
    int msgid;
    key_t key;

    struct msg_buffer message;

    //generate a unique key
    key=ftok("progfile",65);

    //create a messafe queue
    msgid=msgget(key,0666 | IPC_CREAT);

    if(fork()==0){ //child-receiver
        msgrcv(msgid,&message,sizeof(message.number),1,0);
        printf("\nprocess b has received number: %d",message.number);

        if(isPalindrome(message.number)){
            printf("\nit is a palindrome");
        }
        else{
            printf("\nnot a palindrome");
        }
        msgctl(msgid,IPC_RMID,NULL);
    }

    else{ //parent-sender
        printf("\nenter number: ");
        scanf("%d",&message.number);
        message.messageType=1;
        msgsnd(msgid,&message,sizeof(message.number),0);
        printf("\nprocess A has sent %d",message.number);

    }
}
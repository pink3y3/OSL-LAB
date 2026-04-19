//thread management

#include<pthread.h>
#include<stdio.h>

void *thread_code(void *param){
    printf("\nin thread code\n");
}

int main(){
    pthread_t thread;
    pthread_create(&thread,0,&thread_code,0);
    printf("\nin main thread");
    pthread_join(thread,0);
}

/*
#include<pthread.h>
#include<stdio.h>

void *thread_code(void *param){
    printf("\nin thread code\n");
    pthread_exit(NULL);
}

int main(){
    pthread_t thread;
    pthread_create(&thread,0,&thread_code,0);
    printf("\nin main thread");
    pthread_exit(NULL);
}
*/
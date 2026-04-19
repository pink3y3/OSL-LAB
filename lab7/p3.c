//semaphore

#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

sem_t semaphore;
int counter=0;

void *func1(void *param){
    printf("thread1\n ");
    sem_post(&semaphore);
}

void *func2(void *param){   
    sem_wait(&semaphore);
    printf("thread 2\n");
}

int main(){
    pthread_t thread[2];

    sem_init(&semaphore,0,0);
    pthread_create(&thread[0],0,func1,0);
    pthread_create(&thread[1],0,func2,0);
    pthread_join(thread[0],0);
    pthread_join(thread[1],0);
    sem_destroy(&semaphore);
}
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define size 10

sem_t mutex,full,empty;
int in=0,out=0;
int buffer[size];

void *producer(void *arg){
    int item;
    for(int i=0;i<20;i++){
        item=i;

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in]=item;
        printf("produced: %d\n",item);
        in=(in+1)%size;

        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg){
    int item;
    for(int i=0;i<20;i++){

        sem_wait(&full); //first check then lock
        sem_wait(&mutex);

        item=buffer[out];
        printf("consumer: %d\n",item);
        out=(out+1)%size;

        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main(){
    pthread_t p,c;

    sem_init(&mutex,0,1);
    sem_init(&empty,0,size);
    sem_init(&full,0,0);

    pthread_create(&p,NULL,producer,NULL);
    pthread_create(&c,NULL,consumer,NULL);

    pthread_join(p,NULL);
    pthread_join(c,NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
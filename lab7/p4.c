//bounded buffer problem

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define n 5 //buffer size

sem_t mutex,full,empty;
int buffer[n];
int in=0,out=0;

void *producer(void *arg){
    int item;
    for(int i=0;i<10;i++){
        item=i;
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in]=item;
        printf("\nproduced: %d",item);
        in=(in+1)%n;

        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg){
    int item;
    for(int i=0;i<10;i++){
        sem_wait(&full);
        sem_wait(&mutex);

        item=buffer[out];
        printf("\nconsumed: %d",item);
        out=(out+1)%n;

        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}


int main(){
    pthread_t p,c;

    sem_init(&mutex,0,1);
    sem_init(&empty,0,n);
    sem_init(&full,0,0);

    pthread_create(&p,NULL,producer,NULL);
    pthread_create(&c,NULL,consumer,NULL);

    pthread_join(p,NULL);
    pthread_join(c,NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    return 0;
}
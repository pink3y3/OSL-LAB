//dining philosopher problem

#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>

#define n 5

sem_t forks[n];
sem_t room; //limit philosophers

void *philosopher(void *arg){
    int id = *((int *)arg);

    while(1){
        printf("philosopher %d is thinking\n",id);
        sleep(1);
        sem_wait(&room);

        sem_wait(&forks[id]);
        sem_wait(&forks[(id+1)%n]);

        printf("philosopher %d is eating\n",id);
        sleep(1);

        sem_post(&forks[id]);
        sem_post(&forks[(id+1)%n]);

        sem_post(&room);
    }
}

int main(){
    pthread_t p[n];
    int id[n];

    sem_init(&room,0,n-1);

    for(int i=0;i<n;i++){
        sem_init(&forks[i],0,1);
    }

    for(int i=0;i<n;i++){
        id[i]=i;
        pthread_create(&p[i],NULL,philosopher,&id[i]);
    }

    for(int i=0;i<n;i++){
        pthread_join(p[i],NULL);
    }

    return 0;
}
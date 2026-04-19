//reader-writer 
//scoreboard problem - only host can change(write) the values
//fans can read the values. no more than 10 fans at a time

#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex,wrt,fan_limit;
int read_count=0,score=0;

void *fan(void *args){
    int id=*((int *)args);

    sem_wait(&fan_limit);
    sem_wait(&mutex);
    read_count++;
    if(read_count==1){
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    printf("fan %d is reading score: %d\n",id,score);
    sleep(1);

    sem_wait(&mutex);
    read_count--;
    if(read_count==0){
        sem_post(&wrt);
    }
    sem_post(&mutex);
    sem_post(&fan_limit);
    return NULL;

}

void *host(void *args){
    for(int i=1;i<=5;i++){
        sem_wait(&wrt);
        
        score+=10;
        printf("host updated score to %d\n",score);
        sleep(1);

        sem_post(&wrt);
        sleep(1);
    }
    return NULL;
}

int main(){

    pthread_t f[15],h;
    int id[15];

    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);
    sem_init(&fan_limit,0,10);

    pthread_create(&h,NULL,host,NULL);

    for(int i=0;i<15;i++){
        id[i]=i+1;
        pthread_create(&f[i],NULL,fan,&id[i]);
    }
    
    pthread_join(h,NULL);
    for(int i=0;i<15;i++){
        pthread_join(f[i],NULL);
    }


    sem_destroy(&mutex);
    sem_destroy(&wrt);
    sem_destroy(&fan_limit);
}
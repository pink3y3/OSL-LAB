#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t mutex,wrt,limit;
int read_count=0;

void *reader(void *arg){
    int id = *((int *)arg);

    sem_wait(&limit);
    sem_wait(&mutex);
    read_count++;
    if(read_count==1){
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    printf("id %d is reading\n",id);

    sem_wait(&mutex);
    read_count--;
    if(read_count==0){
        sem_post(&wrt);
    }
    sem_post(&mutex);
    sem_post(&limit);
    return NULL;
}

void *host(void *arg){
    for(int i=0;i<10;i++){
        sem_wait(&wrt);
        
        printf("\nhost is changing");
        sem_post(&wrt);
    }
    return NULL;
}

int main(){

    pthread_t r[10],h;
    int id[10];

    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);
    sem_init(&limit,0,5);

    pthread_create(&h,NULL,host,NULL);

    for(int i=0;i<10;i++){
        id[i]=i+1;
        pthread_create(&r[i],NULL,reader,&id[i]);
    }
    pthread_join(h,NULL);
    for(int i=0;i<10;i++){
        pthread_join(r[i],NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    sem_destroy(&limit);
}
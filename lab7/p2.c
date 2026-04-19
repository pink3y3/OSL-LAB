//mutex locks

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t mutex;
int counter=0;

void *count(void *param){
    for(int i=0;i<100;i++){
        pthread_mutex_lock(&mutex);
        counter++;
        printf("count=%i\n",counter);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(){
    pthread_t thread[2];
    pthread_mutex_init(&mutex,0);
    pthread_create(&thread[0],0,count,0);
    pthread_create(&thread[1],0,count,0);
    pthread_join(thread[0],0);
    pthread_join(thread[1],0);
    pthread_mutex_destroy(&mutex);
    return 0;
}
//setting attributes

#include<pthread.h>
#include<stdio.h>

void *child_routine( void *arg){
    printf("thread running\n");
    return NULL;
}

int main(){
    pthread_t thread;
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    pthread_create(&thread,&attributes,child_routine,NULL);
    pthread_join(thread,NULL);
    pthread_attr_destroy(&attributes);
    return 0;
}
//thread management
#include<pthread.h>
#include<stdio.h>

void *child_thread(void *param){
    int id = *(int *)param;
    printf("start thread %d\n", id);
    return param;
}

int main(){
    pthread_t thread[10];
    int ids[10];
    int *return_value;

    for(int i=0;i<10;i++){
        ids[i] = i;
        pthread_create(&thread[i], NULL, child_thread, &ids[i]);
    }

    for(int i=0;i<10;i++){
        pthread_join(thread[i], (void **)&return_value);
        printf("end thread %d\n", *return_value);
    }

    return 0;
}

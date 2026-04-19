#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#define max 10
int c[max][max],n;
int a[max][max],b[max][max];

void *read_matrices(void *args){
    printf("\nenter matrix size: ");
    scanf("%d",&n);
    printf("\nenter elements for A: ");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    printf("\nenter elements for B: ");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&b[i][j]);
        }
    }
    pthread_exit(NULL);
}

void *multiply(void *args){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            c[i][j]=0;
            for(int k=0;k<n;k++){
                c[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

void *display(void *args){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t t[3];
    pthread_create(&t[0],NULL,read_matrices,NULL);
    pthread_join(t[0],NULL);

    pthread_create(&t[1],NULL,multiply,NULL);
    pthread_join(t[1],NULL);

    pthread_create(&t[2],NULL,display,NULL);
    pthread_join(t[2],NULL);

    return 0;
}
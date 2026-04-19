#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

int arr[50],n;

void swap(int *a, int *b){
    int t=*a;
    *a=*b;
    *b=t;
}

void *bubble_sort(void *arg){
    int a[100];
    for(int i=0;i<n;i++) a[i]=arr[i];
    clock_t start=clock();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(a[j]>a[j+1]){
                swap(&a[j],&a[j+1]);
            }
        }
    }
    clock_t end=clock();

    printf("\nbubble sort time: %lf seconds", (double)(end-start)/CLOCKS_PER_SEC);
    pthread_exit(NULL);
}


void *selection_sort(void *arg){
    int a[100];
    for(int i=0;i<n;i++) a[i]=arr[i];
    clock_t start=clock();
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            if(a[j]<a[min]){
                min=j;  
            }
        }
        swap(&a[i],&a[min]);
    }
    clock_t end=clock();
    printf("\nselection sort time: %lf",(double)(end-start)/CLOCKS_PER_SEC);
    pthread_exit(NULL);
}

void *insertion_sort(void *arg){
    int a[100];
    for(int i=0;i<n;i++) a[i]=arr[i];
    clock_t start=clock();
    for(int i=1;i<n;i++){
        int key=a[i];
        int j=i-1;
        while(j>=0 && a[j]>key){
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
    }
    clock_t end=clock();
    printf("\nInsertion Sort Time: %lf seconds",
           (double)(end-start)/CLOCKS_PER_SEC);

    pthread_exit(NULL);
}

int main(){
    
    printf("Enter number of elements: ");
    scanf("%d",&n);

    printf("Enter elements:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    pthread_t t1,t2,t3;

    pthread_create(&t1,NULL,bubble_sort,NULL);
    pthread_create(&t2,NULL,selection_sort,NULL);
    pthread_create(&t3,NULL,insertion_sort,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    printf("\nsorted array: ");
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
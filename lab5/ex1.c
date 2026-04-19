//fcfs-non preemptive

#include<stdio.h>
#include<stdlib.h>

int pid[10],bt[10],at[10];
int wt[10],ct[10],tat[10];
int n;

float avg(int a[]){
    float avg_time=0;
    for(int i=0;i<n;i++){
        avg_time+=a[i];
    }
    return avg_time/n;
}

void swap(int *a, int *b){
    int t=*a;
    *a=*b;
    *b=t;
}

void sort(){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(at[j]>at[j+1]){
                swap(&pid[j],&pid[j+1]);
                swap(&at[j],&at[j+1]);
                swap(&bt[j],&bt[j+1]);
            }
        }
    }
}

void create(){
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("enter process id: ");
    for(int i=0;i<n;i++){
        scanf("%d",&pid[i]);
    }
    printf("enter arrival time: ");
    for(int i=0;i<n;i++){
        scanf("%d",&at[i]);
    }  
    printf("enter burst time: ");
    for(int i=0;i<n;i++){
        scanf("%d",&bt[i]);
    }
    sort();
}

void display(){
    printf("\n |");
    for(int i=0;i<n;i++){
        printf("   %d   |",pid[i]);
    }
    printf("\n%d",at[0]);
    for(int i=0;i<n;i++){
        printf("     %d",ct[i]);
    }
    printf("\navg. wt: %0.2f",avg(wt));
    printf("\navg. tat: %0.2f",avg(tat));
}

void fcfs(){
    ct[0]=at[0]+bt[0];
    for(int i=1;i<n;i++){
        if(ct[i-1]<at[i]){
            ct[i]=at[i]+bt[i];
        }
        else{
            ct[i]=ct[i-1]+bt[i];
        }
    }
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }
}

int main(){
    create();
    fcfs();
    display();
    return 0;
}
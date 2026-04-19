//sjf-non preemptive

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
}

void display(){
    printf("\navg. wt: %0.2f",avg(wt));
    printf("\navg. tat: %0.2f",avg(tat));
}

void sjf(){
    int completed=0,time=0; 
    int visited[10]={0};
    int order[10],k=0; 

    while(completed<n){
        int min_index=-1; 
        for(int i=0;i<n;i++){ 
            if(at[i]<=time && !visited[i]){ 
                if(min_index==-1 || bt[i]<bt[min_index]){ 
                    min_index=i;
                }
            }
        }
        if(min_index==-1){ //if no process available
            time++;
            continue;
        }

        time+=bt[min_index];
        ct[min_index]=time;
        order[k++]=min_index;
        visited[min_index]=1;
        completed++;
    }

    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }
    printf("\n|");
    for(int i=0;i<n;i++){
        printf("   P%d   |",pid[order[i]]);
    }
    printf("\n%d",at[0]);
    for(int i=0;i<n;i++){
        printf("       %d",ct[order[i]]);
    }
}

int main(){
    create();
    sjf();
    display();
    return 0;
}
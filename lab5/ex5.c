//non preemptive priority
#include <stdio.h>

int pid[10], bt[10], at[10], pri[10];
int wt[10], ct[10], tat[10];
int n;

float avg(int a[]) {
    float sum = 0;
    for(int i=0; i<n; i++) sum += a[i];
    return sum/n;
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
    printf("enter priority: ");
    for(int i=0;i<n;i++){
        scanf("%d",&pri[i]);
    }
}

void npp() {
    int completed=0,k=0,time=0;
    int visited[10]={0},order[n];

    while(completed<n){
        int idx=-1;
        for(int i=0;i<n;i++){
            if(at[i]<=time && !visited[i]){
                if(idx==-1 ||
                    pri[i]<pri[idx]||
                    pri[i]==pri[idx] && at[i]<at[idx] ||
                    pri[i]==pri[idx] && at[i]==at[idx] && pid[i]<pid[idx]){
                        idx=i;
                    }
            }
        }
        
        if(idx==-1){
            time++;
            continue;
        }

        time+=bt[idx];
        ct[idx]=time;
        order[k++]=idx;
        visited[idx]=1;
        completed++;

        for(int i=0;i<n;i++){
            tat[i]=ct[i]-at[i];
            wt[i]=tat[i]-bt[i];
        }

        printf("\nGantt chart: \n");

        for(int i=0;i<k;i++){
            printf("  P%d  |",pid[order[i]]);
        }
        printf("\n0");
        for(int i=0;i<k;i++){
            printf("    %d",ct[order[i]]);
        }
    }
    printf("\nAverage WT: %.2f", avg(wt));
    printf("\nAverage TAT: %.2f\n", avg(tat));
}

int main() {
    create();
    npp();
    return 0;
}
//earliest deadline first

#include<stdio.h>

int pid[10], bt[10], at[10], dl[10];
int rt[10], ct[10], wt[10], tat[10];
int gantt[100];
int n;

float avg(int a[]){
    float sum=0;
    for(int i=0;i<n;i++) sum+=a[i];
    return sum/n;
}

void create(){
    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter process id: ");
    for(int i=0;i<n;i++)
        scanf("%d",&pid[i]);

    printf("Enter arrival time: ");
    for(int i=0;i<n;i++)
        scanf("%d",&at[i]);

    printf("Enter burst time: ");
    for(int i=0;i<n;i++){
        scanf("%d",&bt[i]);
        rt[i]=bt[i];
    }

    printf("Enter deadline: ");
    for(int i=0;i<n;i++)
        scanf("%d",&dl[i]);
}

void edf(){
    int completed=0,time=0;
    int k=0;

    while(completed<n){
        int idx=-1;
        for(int i=0;i<n;i++){
            if(at[i]<=time && rt[i]>0){
                if(idx==-1||
                    dl[i]<dl[idx]||
                    dl[i]==dl[idx] && at[i]<at[idx]||
                    dl[i]==dl[idx] && at[i]==at[idx] && pid[i]<pid[idx]){
                        idx=i;
                    }
            }
        }

        if(idx==-1){
            gantt[k++]=-1;
            time++;
            continue;
        }

        gantt[k++]=idx;
        rt[idx]--;
        time++;

        if(rt[idx]==0){
            ct[idx]=time;
            completed++;
        }

        for(int i=0;i<n;i++){
            tat[i]=ct[i]-at[i];
            wt[i]=tat[i]-bt[i];
        }

        printf("\nGantt chart: \n");
        for(int i=0;i<k;i++){
            if(gantt[i]==-1){
                printf("  idle |");
            }
            else{
                printf(" P%d   |",pid[gantt[i]]);
            }
        }
        printf("\n0");
        for(int i=0;i<k;i++){
            printf("     %d",ct[gantt[i]]);
        }
    }
}

void display(){
    printf("\nAvg WT: %.2f", avg(wt));
    printf("\nAvg TAT: %.2f\n", avg(tat));
}

int main(){
    create();
    edf();
    display();
    return 0;
}
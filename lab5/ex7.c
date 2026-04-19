//multilevel queue

#include<stdio.h>

int pid[10], bt[10], at[10];
int ct[10], wt[10], tat[10];
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
    for(int i=0;i<n;i++)
        scanf("%d",&bt[i]);
}

void mlq(){
    int time = 0;

    printf("\nGantt Chart:\n|");
    printf("0");

    // 🔹 Queue 1 → FCFS (first half)
    for(int i=0;i<n/2;i++){
        if(time < at[i]) time = at[i];

        printf(" P%d |", pid[i]);

        time += bt[i];
        ct[i] = time;

        printf(" %d", time);
    }

    for(int i=n/2;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(bt[j] < bt[i]){
                // swap bt
                int temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // swap pid
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;

                // swap at
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
            }
        }
    }

    for(int i=n/2;i<n;i++){
        if(time < at[i]) time = at[i];

        printf(" P%d |", pid[i]);

        time += bt[i];
        ct[i] = time;

        printf(" %d", time);
    }

    for(int i=0;i<n;i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}

void display(){
    printf("\nAvg WT: %.2f", avg(wt));
    printf("\nAvg TAT: %.2f\n", avg(tat));
}

int main(){
    create();
    mlq();
    display();
    return 0;
}
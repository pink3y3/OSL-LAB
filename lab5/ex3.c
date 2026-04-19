//srtf

#include<stdio.h>
#include<stdlib.h>

int pid[10], bt[10], at[10];
int rt[10];
int wt[10], ct[10], tat[10];
int gantt[100]; 
int n;

float avg(int a[]) {
    float sum = 0;
    for(int i = 0; i < n; i++) sum += a[i];
    return sum / n;
}

void create() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter PIDs: ");
    for(int i = 0; i < n; i++) scanf("%d", &pid[i]);
    printf("Enter Arrival Times: ");
    for(int i = 0; i < n; i++) scanf("%d", &at[i]);
    printf("Enter Burst Times: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }
}

void srtf() {
    int completed = 0, time = 0, k = 0; 

    while(completed < n) { 
        int min_index = -1; 
        for(int i = 0; i < n; i++) { 
            if(at[i] <= time && rt[i] > 0) { 
                if(min_index == -1 || rt[i] < rt[min_index]) { 
                    min_index = i;
                }
            }
        }

        if(min_index == -1) { 
            gantt[k++] = -1;
            time++;
            continue;
        }

        gantt[k++] = min_index;
        rt[min_index]--;
        time++;

        if(rt[min_index] == 0) {
            ct[min_index] = time;
            completed++;
        }
    }

    // Calculate metrics once execution is finished
    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // --- PRINTING MOVED OUTSIDE THE WHILE LOOP ---
    printf("\nGantt Chart:\n|");
    for(int i = 0; i < k; i++) {
       if(gantt[i] == -1) printf(" idle |");
       else printf("  P%d  |", pid[gantt[i]]);
    }

    printf("\n0");
    for(int i = 0; i < k; i++) {
        // Dynamic spacing to match process blocks
        printf("      %d", i + 1);
    }

    printf("\n\nAvg. WT: %0.2f", avg(wt));
    printf("\nAvg. TAT: %0.2f\n", avg(tat));
}

int main() {
    create();
    srtf();
    return 0;
}
//round robin
#include <stdio.h>
#include <stdlib.h>

int pid[10], bt[10], at[10], rt[10], wt[10], tat[10];
int queue[100], front = 0, rear = 0; // Fixed syntax
int n, tq;
int visited[10] = {0};
int gantt[200], gant_time[200];

void push(int i) {
    queue[rear++] = i;
}

int pop() {
    return queue[front++];
}

float avg(int a[]) {
    float sum = 0;
    for(int i = 0; i < n; i++) sum += a[i];
    return sum / n;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void sort() {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(at[j] > at[j + 1]) {
                swap(&pid[j], &pid[j + 1]);
                swap(&at[j], &at[j + 1]);
                swap(&bt[j], &bt[j + 1]);
            }
        }
    }
}

void create() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter process IDs: ");
    for(int i = 0; i < n; i++) scanf("%d", &pid[i]);
    printf("Enter arrival times: ");
    for(int i = 0; i < n; i++) scanf("%d", &at[i]);
    printf("Enter burst times: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; 
    }
    sort();
}

void round_robin(int quantum) {
    int completed = 0, time = at[0], k = 0;
    push(0);
    visited[0] = 1;

    while(completed < n) {
        // Handle CPU Idle
        if(front == rear) {
            time++;
            for(int m = 0; m < n; m++) {
                if(at[m] <= time && !visited[m] && rt[m] > 0) {
                    push(m);
                    visited[m] = 1;
                }
            }
            continue;
        }

        int curr = pop();
        int t = (rt[curr] < quantum) ? rt[curr] : quantum;
        
        // Execute and check for arrivals at each time unit
        for(int j = 0; j < t; j++) {
            time++;
            for(int m = 0; m < n; m++) {
                if(at[m] <= time && !visited[m] && rt[m] > 0) {
                    push(m);
                    visited[m] = 1;
                }
            }
        }

        rt[curr] -= t;
        gantt[k] = pid[curr];
        gant_time[k] = time;
        k++;

        if(rt[curr] > 0) {
            push(curr); // New arrivals were pushed first, then current
        } else {
            completed++;
            tat[curr] = time - at[curr];
            wt[curr] = tat[curr] - bt[curr];
        }
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n|");
    for(int i = 0; i < k; i++) {
        printf(" P%d |", gantt[i]);
    }

    printf("\n0");
    for(int i = 0; i < k; i++) {
        printf("   %d", gant_time[i]);
    }

    // Print averages
    printf("\n\nAverage WT: %.2f", avg(wt));
    printf("\nAverage TAT: %.2f\n", avg(tat));
}

int main() {
    create();
    printf("Enter time quantum: ");
    int q;
    scanf("%d", &q);
    round_robin(q);
    return 0;
}
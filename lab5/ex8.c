//multilevel feedback queue

#include <stdio.h>

typedef struct {
    int pid, at, bt, rt, ct, tat, wt;
} Process;

void mlfq() {
    int n, tq1, tq2, time = 0, completed = 0;
    Process p[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum for Q1 and Q2: ");
    scanf("%d %d", &tq1, &tq2);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d Arrival & Burst: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("\nGantt Chart:\n0");

    while (completed < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].rt == p[i].bt) {
                int exec = (p[i].rt > tq1) ? tq1 : p[i].rt;
                time += exec;
                p[i].rt -= exec;
                printf(" -> P%d -> %d", p[i].pid, time);
                if (p[i].rt == 0) { p[i].ct = time; completed++; }
                found = 1;
            }
        }

        if (!found) {
            for (int i = 0; i < n; i++) {

                if (p[i].at <= time && p[i].rt > 0 && p[i].rt > (p[i].bt - tq1 - tq2)) {
                    int exec = (p[i].rt > tq2) ? tq2 : p[i].rt;
                    time += exec;
                    p[i].rt -= exec;
                    printf(" -> P%d -> %d", p[i].pid, time);
                    if (p[i].rt == 0) { p[i].ct = time; completed++; }
                    found = 1;
                    break; 
                }
            }
        }

        if (!found) {
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && p[i].rt > 0) {
                    time += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = time;
                    completed++;
                    printf(" -> P%d -> %d", p[i].pid, time);
                    found = 1;
                    break;
                }
            }
        }

        if (!found) time++; 
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

int main() {
    mlfq();
    return 0;
}
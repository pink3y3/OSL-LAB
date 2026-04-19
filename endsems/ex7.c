#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void display(int n, int m, int matrix[n][m]){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

bool isSafe(int n, int m, int alloc[n][m], int need[n][m], int avail[m]){

    int finish[n], work[m], safeSeq[n];

    for(int i=0;i<n;i++) finish[i] = 0;
    for(int i=0;i<m;i++) work[i] = avail[i];

    int count = 0;

    while(count < n){
        bool found = false;

        for(int i=0;i<n;i++){
            if(finish[i] == 0){
                bool possible = true;

                for(int j=0;j<m;j++){
                    if(need[i][j] > work[j]){
                        possible = false;
                        break;
                    }
                }

                if(possible){
                    for(int j=0;j<m;j++){
                        work[j] += alloc[i][j];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }

        if(!found){
            printf("\nSystem is NOT in safe state\n");
            return false;
        }
    }

    printf("\nSystem is in safe state\nSafe Sequence: ");
    for(int i=0;i<n;i++){
        printf("P%d ", safeSeq[i]);
    }

    printf("\n");
    return true;
}

void isRequest(int n, int m,
               int alloc[n][m],
               int max[n][m],
               int need[n][m],
               int avail[m]){

    int pid, req[m];

    printf("\nEnter process id: ");
    scanf("%d", &pid);

    printf("Enter request vector: ");
    for(int i=0;i<m;i++){
        scanf("%d", &req[i]);
    }

    // Check Request <= Need
    for(int i=0;i<m;i++){
        if(req[i] > need[pid][i]){
            printf("\nError: Request exceeds maximum claim\n");
            return;
        }
    }

    // Check Request <= Available
    for(int i=0;i<m;i++){
        if(req[i] > avail[i]){
            printf("\nResources not available. Process must wait.\n");
            return;
        }
    }

    // Backup
    int tempAlloc[n][m], tempNeed[n][m], tempAvail[m];

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            tempAlloc[i][j] = alloc[i][j];
            tempNeed[i][j] = need[i][j];
        }
    }

    for(int i=0;i<m;i++){
        tempAvail[i] = avail[i];
    }

    // Pretend allocation
    for(int j=0;j<m;j++){
        avail[j] -= req[j];
        alloc[pid][j] += req[j];
        need[pid][j] -= req[j];
    }

    // Safety check after allocation
    if(isSafe(n, m, alloc, need, avail)){
        printf("Request is GRANTED\n");
    }
    else{
        printf("Request is NOT safe. Rolling back...\n");

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                alloc[i][j] = tempAlloc[i][j];
                need[i][j] = tempNeed[i][j];
            }
        }

        for(int i=0;i<m;i++){
            avail[i] = tempAvail[i];
        }
    }
}

int main(){

    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m];

    printf("\nEnter Allocation Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Max Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Vector:\n");
    for(int j=0;j<m;j++){
        scanf("%d", &avail[j]);
    }

    // Compute Need matrix
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nNeed Matrix:\n");
    display(n, m, need);

    // Initial safety check
    isSafe(n, m, alloc, need, avail);

    // Request handling
    isRequest(n, m, alloc, max, need, avail);

    return 0;
}
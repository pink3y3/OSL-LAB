//safety sequence and request allocation

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int n,m;

void display(int arr[n][m]){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}

bool isSafe(int alloc[n][m], int max[n][m], int available[m]){
    int need[n][m];

    printf("need matrix: \n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j]=max[i][j]-alloc[i][j];
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }

    int work[m];
    bool finish[n];

    for(int i=0;i<n;i++){
        finish[i]=false;
    }

    for(int i=0;i<m;i++){
        work[i]=available[i];
    }

    int count=0;

    while(count<n){
        bool found=false;

        for(int i=0;i<n;i++){
            if(!finish[i]){
                bool possible=true;

                for(int j=0;j<m;j++){
                    if(need[i][j]>work[j]){
                        possible=false;
                        break;
                    }
                }

                if(possible){
                    for(int j=0;j<m;j++){
                        work[j]+=alloc[i][j];
                    }

                    finish[i]=true;
                    found=true;
                    count++;
                }   
            }            
        }
        if(!found){
            return false;
        }
    }
    return true;
}

bool isRequest(int alloc[n][m],int max[n][m],int available[m]){
    int p,request[m];
    printf("\nenter process: ");
    scanf("%d",&p);
    printf("\nenter request matrix of process: ");
    for(int i=0;i<m;i++){
        scanf("%d",&request[i]);
    }

    int need[n][m];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }

    for(int j=0;j<m;j++){
        if(request[j]>need[p][j]){
            printf("error: request exceeds maximum claim");
            return false;
        }
    }
    for(int j=0;j<m;j++){
        if(request[j]>available[j]){
            printf("process must wait");
            return false;
        }
    }
    int tempAlloc[n][m];
    int tempAvail[m];
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            tempAlloc[i][j]=alloc[i][j];
        }
    }

    for(int j=0;j<m;j++){
        tempAvail[j]=available[j];
    }

    for(int j=0;j<m;j++){
        available[j]-=request[j];
        alloc[p][j]+=request[j];
    }

    if(isSafe(alloc,max,available)){
        printf("\nrequest granted immediately");
        printf("\nallocation matrix:\n");
        display(alloc);
        printf("\nneed matrix:\n");
        display(need);
        printf("\navailable matrix:\n");
        for(int i=0;i<m;i++){
            printf("%d ",available[i]);
        }
        return true;
    }
    else{
        for(int j=0;j<m;j++){
            available[j]=tempAvail[j];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                alloc[i][j]=tempAlloc[i][j];
            }
        }
        printf("\nrequest denied");
        return false;
    }

}

int main(){
    printf("enter number of processes: ");
    scanf("%d",&n);
    printf("enter number of resource types: ");
    scanf("%d",&m);

    int alloc[n][m],max[n][m],available[m];

    printf("enter allocation matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&alloc[i][j]);
        }
    }

    printf("enter max matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&max[i][j]);
        }
    }

    printf("enter available matrix:\n");
    for(int i=0;i<m;i++){
       scanf("%d",&available[i]);
    }
    
    if(isSafe(alloc,max,available)){
        printf("\nsystem is in safe state\n");
    }
    else{
        printf("\nsystem is in unsafe state\n");
    }

    isRequest(alloc,max,available);
    isRequest(alloc,max,available);
    isRequest(alloc,max,available);
}
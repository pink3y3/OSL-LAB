#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int n,m;
void display(int matrix[n][m]){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

bool isDetect(int alloc[n][m], int request[n][m], int available[m]){
    int work[m];
    bool finish[n];

    for(int i=0;i<m;i++){
        work[i]=available[i];
    }

    for (int i=0;i<n;i++){
        finish[i]=false;
    }
    
    for(int i=0;i<n;i++){
        bool zero=true;
        for(int j=0;j<m;j++){
            if(alloc[i][j]!=0){
                zero=false;
                break;
            }
        }
        finish[i]=zero;
    }

    int count=0;

    while(count<n){
        bool found=false;

        for(int i=0;i<n;i++){
            if(!finish[i]){
                bool possible=true;
                for(int j=0;j<m;j++){
                    if(request[i][j]>work[j]){
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
                break;
            }
        }

    for(int i=0;i<n;i++){
        if(!finish[i]){
            return true;
        }
    }
    return false;
}



int main(){
    printf("Enter number of processes: ");
    scanf("%d",&n);
    printf("enter number of resource types: ");
    scanf("%d",&m);

    int alloc[n][m],request[n][m],available[m];

    printf("enter allocation matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&alloc[i][j]);
        }
    }

    printf("enter request matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&request[i][j]);
        }
    }

    printf("enter available matrix:\n");
    for(int i=0;i<m;i++){
       scanf("%d",&available[i]);
    }
    
    if(isDetect(alloc,request,available)){
        printf("\nsystem is deadlocked\n");
    }
    else{
        printf("\nsystem is not deadlocked\n");
    }

    request[2][2]++;
    if(isDetect(alloc,request,available)){
        printf("\nsystem is deadlocked\n");
    }
    else{
        printf("\nsystem is not deadlocked\n");
    }

}

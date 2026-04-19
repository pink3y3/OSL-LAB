//memory allocation using best fit and safety check
#include<stdio.h>

void sort(int block_size[], int m){
    for(int k=0;k<m;k++){
            for(int j=0;j<m-k-1;j++){
                if(block_size[j]<block_size[j+1]){
                    int temp=block_size[j];
                    block_size[j]=block_size[j+1];
                    block_size[j+1]=temp;
                }
            }
        }
}


int main(){
    int n,m;

    printf("enter number of processes: ");
    scanf("%d", &n);
    printf("enter number of memory blocks: ");
    scanf("%d", &m);

    int block_size[m], process_size[n];

    printf("enter process sizes: ");
    for(int i=0;i<n;i++){
        scanf("%d",&process_size[i]);
    }

    printf("enter memory block sizes: ");
    for(int i=0;i<m;i++){
        scanf("%d",&block_size[i]);
    }

    int alloc[n];
    for(int i=0;i<n;i++) alloc[i]=0;
    
    int p=0;
    int pid[n],req_memory[n];
    printf("enter request id and memory required: ");
    while(1){
        scanf("%d",&pid[p]);
        if(pid[p]==-1) break;
        scanf("%d",&req_memory[p]);
        p++;
    }


    for(int i=0;i<p;i++){

        sort(block_size,m);

        printf("\nP%d request %d", pid[i],req_memory[i]);
        printf("\nBefore: ");
        for(int j=0;j<m;j++){
            printf("%d ",block_size[j]);
        }

        int idx=-1;

        for(int j=m-1;j>=0;j--){
            if(req_memory[i]<=block_size[j]){
                idx=j;
                break;
            }
        }
        if(idx!=-1){
            block_size[idx]-=req_memory[i];
            alloc[pid[i]]+=req_memory[i];
        }
        else{
            printf("\nnot possible");
            continue;
        }

        sort(block_size,m);

        printf("\nAfter: ");
        for(int j=0;j<m;j++){
            printf(" %d ",block_size[j]);
        }

        int total=0;

        for(int j=0;j<m;j++){
            total+=block_size[j];
        }

        int finish[n];

        for(int x=0;x<n;x++) finish[x]=0;
        int safeSeq[n];

        int count=0;


        while(count<n){
            int found=0;

            for(int j=0;j<n;j++){
                int need=process_size[j]-alloc[j];
                if(finish[j]!=1 && need<=total){
                    total+=alloc[j];
                    safeSeq[count++]=j;
                    finish[j]=1;
                    found=1;
                }
            }

            if(!found) break;
        }

        if(count==n){
            printf("\nSafe | Seq: ");
            for(int j=0;j<n;j++){
                printf("P%d ",safeSeq[j]);
            }
        }
        else{
            printf("\nunsafe state");
        }
    }
}
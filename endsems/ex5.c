#include<stdio.h>
#include<stdlib.h>

void sort(int block_size[], int m){
    for(int i=0;i<m;i++){
        for(int j=0;j<m-i-1;j++){
            if(block_size[j]>block_size[j+1]){
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
    scanf("%d",&m);

    int process_size[n],block_size[m],alloc[n];

    for(int i=0;i<n;i++) alloc[i]=0;

    printf("enter processes sizes: ");
    for(int i=0;i<n;i++) scanf("%d",&process_size[i]);

    printf("enter block sizes: ");
    for(int i=0;i<m;i++) scanf("%d",&block_size[i]);

    int p=0;
    int pid[n],req_size[n];

    printf("enter request pid,memory | -1 to exit: ");
    while(1){
        scanf("%d",&pid[p]);
        if(pid[p]==-1) break;
        scanf("%d",&req_size[p]);
        p++;
    }

    int idx=-1;
    
    for(int i=0;i<p;i++){
        printf("\nP%d request %d",pid[i],req_size[i]);
        sort(block_size,m);
        printf("\nbefore: ");
        for(int j=0;j<m;j++) printf("%d ",block_size[j]);

        int start=(idx==-1)?0:idx;
        int newIdx=-1;
        
        for(int j=0;j<m;j++){
            int k=(start+j)%m;
            if(block_size[k]>=req_size[i]){
                newIdx=k;
                break;
            }
        }

        idx=newIdx;
        
        if(idx!=-1){
            block_size[idx]-=req_size[i];
            alloc[pid[i]]+=req_size[i];
        }
        else{
            printf("\nrequest not allocated");
            continue;
        }

        sort(block_size,m);
        printf("\nAfter: ");
        for(int j=0;j<m;j++) printf("%d ",block_size[j]);

        //safety check
        int total=0;
        int safeSeq[n],finish[n];

        for(int x=0;x<n;x++) finish[x]=0;

        for(int j=0;j<m;j++) total+=block_size[j];

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

            if(found==0) break;
        }
        if(count==n){
            printf("\nsafe | seq: ");
            for(int k=0;k<n;k++){
                printf("\nP%d ",safeSeq[k]);
            }
        }
    }
}
//sstf disk scheduling
#include<stdio.h>
#include<stdlib.h>

int main(){
    int head,n,total=0;

    printf("enter number of requests: ");
    scanf("%d",&n);

    int req[n];

    printf("enter request sequence: ");
    for(int i=0;i<n;i++){
        scanf("%d", &req[i]);
    }

    printf("enter head position: ");
    scanf("%d", &head);

    int visited[n],order[n];

    for(int i=0;i<n;i++){
        visited[i]=0;
        order[i]=0;
    }

    for(int i=0;i<n;i++){
        int min_seek=999;
        int idx=-1;
        for(int j=0;j<n;j++){
            if(visited[j]!=1 && abs(head-req[j])<min_seek){
                min_seek=abs(head-req[j]);
                idx=j;
            }
        }
        visited[idx]=1;
        order[i]=idx;
        total+=abs(head-req[idx]);
        head=req[idx];
    }

    printf("\nseek sequence: ");
    for(int i=0;i<n;i++){
        printf("%d ",req[order[i]]);
    }

    printf("\ntotal head movement: %d",total);
    return 0;

}
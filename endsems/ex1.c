//Implement LSTF (Largest Seek Time First) disk scheduling along with MFU (Most Frequently Used) page replacement.

#include<stdio.h>
#include<stdlib.h>

int main(){
    int f,head;
    int page[20],cyl[20];

    printf("enter number of frames: ");
    scanf("%d",&f);

    printf("enter head position: ");
    scanf("%d",&head);

    int n=0;

    printf("enter (page,cylinder) pair /-1 to exit: ");
    while(1){
        scanf("%d",&page[n]);
        if(page[n]==-1) break;
        scanf("%d",&cyl[n]);
        n++;
    }

    int visited[20]={0};
    int order[20];

    for(int i=0;i<n;i++){
        int max_seek=-1;
        int max_idx=-1;
        for(int j=0;j<n;j++){
            if(visited[j]!=1 && abs(cyl[j]-head)>max_seek){
                max_seek=abs(cyl[j]-head);
                max_idx=j;
            }
        }

        visited[max_idx]=1;
        order[i]=max_idx;
        head=cyl[max_idx];
    }

    printf("LSTF order: ");
    for(int i=0;i<n;i++){
        printf("%d -> ",cyl[order[i]]);
    }

    printf("\nPage sequence: ");
    for(int i=0;i<n;i++){
        printf("%d ",order[i]+1);
    }

    int pages[n];
    for(int i=0;i<n;i++){
        pages[i]=page[order[i]];
    }

    int frames[f],count[f];

    for(int i=0;i<f;i++){
        frames[i]=-1;
        count[i]=0;
    }

    int fault=0;

    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<f;j++){
            if(frames[j]==pages[i]){
                found=1;
                count[j]++;
                break;
            }
        }

        if(found==0){
            int idx=-1;
            for(int j=0;j<f;j++){
                if(frames[j]==-1){
                    idx=j;
                    break;
                }
            }

            if(idx==-1){
                int max_count=-1;
                idx=0;
                for(int j=0;j<f;j++){
                    if(count[j]>max_count){
                        max_count=count[j];
                        idx=j;
                    }
                }
            }

            frames[idx]=pages[i];
            count[idx]=1;
            fault++;
        }
    }
    
    printf("\nPage faults: %d\n", fault);
    return 0;
}
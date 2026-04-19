//LRU page replacement algorithm

#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,frame;

    printf("enter number of pages: ");
    scanf("%d",&n);

    int *pages=(int *)malloc(n*sizeof(int));

    printf("enter page reference string: ");
    for(int i=0;i<n;i++){
        scanf("%d",&pages[i]);
    }
    
    printf("enter number of frames: ");
    scanf("%d",&frame);

    int *frames=(int *)malloc(frame*sizeof(int));
    int *time=(int *)malloc(frame *sizeof(int));

    for(int i=0;i<frame;i++){
        frames[i]=-1;
        time[i]=0;
    }

    int fault=0,t=0;

    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<frame;j++){
            if(frames[j]==pages[i]){
                found=1;
                t++;
                time[j]=t;
                break;
            }
        }

        if(found==0){
            int lru_idx=0;
            for(int j=1;j<frame;j++){
                if(time[j]<time[lru_idx]){
                    lru_idx=j;
                }
            }
            frames[lru_idx]=pages[i];
            t++;
            time[lru_idx]=t;
            fault++;
        }
    }

    printf("LRU Page Faults = %d\n", fault);
    printf("Hit Ratio = %.2f\n", (float)(n - fault) / n);

    free(pages);
    free(frames);
    free(time);
    return 0;    
}
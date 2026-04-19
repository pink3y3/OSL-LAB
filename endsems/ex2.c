//LCFS disk scheduling with LFU paging algorithm

#include<stdio.h>
#include<stdlib.h>

int main(){
    int f,head,page[20],cyl[20];

    printf("enter number of frames: ");
    scanf("%d", &f);

    printf("enter head position: ");
    scanf("%d", &head);

    int n=0; 

    printf("enter (page & cyl) | -1 to exit: ");
    while(1){
        scanf("%d",&page[n]);
        if(page[n]==-1) break;
        scanf("%d",&cyl[n]);
        n++;
    }

    int order[n];

    for(int i=0;i<n;i++){
        order[i]=n-i-1;
    }

    printf("\nScheduling order: ");
    for(int i=0;i<n;i++){
        printf("%d -> ",cyl[order[i]]);
    }

    printf("\nPage request sequence: ");
    for(int i=0;i<n;i++){
        printf("%d ",order[i]);
    }

    //LFU
    int pages[n], frames[f], count[f];
    int fault=0;
    
    for(int i=0;i<n;i++){
        pages[i]=order[i];
    }

    for(int i=0;i<f;i++){
        frames[i]=-1;
        count[i]=0;
    }

    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<f;j++){
            if(frames[j]==pages[i]){
                count[j]++;
                found=1;
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
                int min_count=count[0];
                idx=0;
                for(int j=0;j<f;j++){
                    if(count[j]<min_count){
                        min_count=count[j];
                        idx=j;
                    }
                }
            }
            frames[idx]=pages[i];
            count[idx]=1;
            fault++;
        }
    }
    printf("\nPage faults: %d", fault);
}

//FIFO page-replacement

#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,frame;

    printf("\nenter number of pages: ");
    scanf("%d",&n);

    int *pages=(int *)malloc(n*sizeof(int));

    printf("\nenter reference string: ");
    for(int i=0;i<n;i++){
        scanf("%d",&pages[i]);
    }

    printf("\nenter number of frames: ");
    scanf("%d",&frame);

    int *frames =(int *)malloc(frame*sizeof(int));

    for(int i=0;i<frame;i++){
        frames[i]=-1;
    }

    int fault=0,index=0;

    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<frame;j++){
            if(frames[j]==pages[i]){
                found++;
                break;
            }
        }

        if(found==0){
            frames[index]=pages[i];
            index=(index+1)%frame;
            fault++;
        }
    }

    printf("\nNumber of page faults: %d",fault);
    printf("\nHit ratio: %0.2f\n",(float)(n-fault)/n);
    free(pages);
    free(frames);

    return 0;
}
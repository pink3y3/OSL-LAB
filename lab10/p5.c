//second chance-clock algorithm

#include<stdio.h>
#include<stdlib.h>

int main(){
    int n, frame;

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
    int *ref=(int *)malloc(frame*sizeof(int));

    for(int i=0;i<frame;i++){
        frames[i]=-1;
        ref[i]=0;
    }

    int fault=0;
    int pointer=0;

    for(int i=0;i<n;i++){
        int found=0;

        for(int j=0;j<frame;j++){
            if(frames[j]==pages[i]){
                ref[j]=1;
                found=1;
                break;
            }
        }

        if(found==0){
            fault++;

            while(1){
                if(ref[pointer]==0){
                    frames[pointer]=pages[i];
                    ref[pointer]=1;
                    pointer=(pointer+1)%frame;
                    break;
                }
                else{
                    ref[pointer]=0;
                    pointer=(pointer+1)%frame;
                }
            }
        }
    }

    printf("\n page faults: %d",fault);
    return 0;
}
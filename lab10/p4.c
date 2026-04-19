//Additional reference byte

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
    int *refBytes=(int *)malloc(frame*sizeof(int));

    for(int i=0;i<frame;i++){
        frames[i]=-1;
        refBytes[i]=0;
    }

    int fault=0;

    for(int i=0;i<n;i++){
        int found=0;

        for(int j=0;j<frame;j++){
            refBytes[j]>>=1;
        }

        for(int j=0;j<frame;j++){
            if(frames[j]==pages[i]){
                found++;
                refBytes[j]|=128; //mark existing page as used
                break;
            }
        }

        if(found==0){
            int idx=-1;

            for(int j=0;j<frame;j++){
                if(frames[j]==-1){
                    idx=j;
                    break;
                }
            }

        if(idx==-1){
            int min=refBytes[0];
            idx=0;
            for(int j=1;j<frame;j++){
                if(refBytes[j]<min){
                    min=refBytes[j];
                    idx=j;
                }
            }
        }
            frames[idx]=pages[i];
            refBytes[idx]=128; //initialise new page just used
            fault++;
        }
    }
    printf("\npage faults: %d",fault);
    return 0;
}
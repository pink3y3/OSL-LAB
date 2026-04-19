//MFU algorithm

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
    int *count=(int *)malloc(frame*sizeof(int));

    for(int i=0;i<frame;i++){
        frames[i]=-1;
        count[i]=0;
    }

    int fault=0;

    for(int i=0;i<n;i++){
        int found=0;

        for(int j=0;j<frame;j++){
            if(frames[j]==pages[i]){
                count[j]++;
                found++;
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
                int max=count[0];
                idx=0;
                for(int j=1;j<frame;j++){
                    if(count[j]>max){
                        idx=j;
                        max=count[idx];
                    }
                }
            }
            frames[idx]=pages[i];
            count[idx]=1;
            fault++;
        }
    }
    printf("Page Faults = %d\n", fault);

    free(pages);
    free(frames);
    free(count);
}
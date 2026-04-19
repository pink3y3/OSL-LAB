//optimal page replacement 

#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,frame;

    printf("enter number of pages: ");
    scanf("%d",&n);
    int *pages = (int *)malloc(n*sizeof(int));
    printf("enter page reference string: ");
    for(int i=0;i<n;i++){
        scanf("%d",&pages[i]);
    }

    printf("enter number of frames: ");
    scanf("%d",&frame);
    int *frames=(int *)malloc(frame*sizeof(int));

    for(int i=0;i<frame;i++){
        frames[i]=-1;
    }

    int fault=0;

    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<frame;j++){
            if(frames[j]==pages[i]){
                found++;
                break;
            }
        }

        if(found==0){
            int replace_idx=-1, farthest_idx=-1;
            for(int j=0;j<frame;j++){
                int k;
                for(k=i+1;k<n;k++){
                    if(frames[j]==pages[k]){
                        break;
                    }
                }
                if(k==n){
                    replace_idx=j;
                    break;
                }

                if(k>farthest_idx){
                    farthest_idx=k;
                    replace_idx=j;
                }
            }
            if(replace_idx==-1) replace_idx=0;

            fault++;
            frames[replace_idx]=pages[i];
        }
    }
    printf("Optimal Page Faults = %d\n", fault);
    printf("Hit Ratio = %.2f\n", (float)(n - fault) / n);

    free(pages);
    free(frames);
    return 0;
    
}
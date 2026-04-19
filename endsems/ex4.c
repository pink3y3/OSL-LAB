//MRU page replacement algo using reference registers

#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,f;

    printf("enter number of pages: ");
    scanf("%d",&n);

    printf("enter number of frames: ");
    scanf("%d",&f);

    int page[n];
    printf("enter reference string: ");
    for(int i=0;i<n;i++){
        scanf("%d", &page[i]);
    }

    int frame[f];
    int ref[f];
    for(int i=0;i<f;i++){
        frame[i]=-1;
        ref[i]=0;
    }

    int fault=0,hit=0;

    for(int i=0;i<n;i++){
        int found=-1;

        for(int j=0;j<f;j++){
            if(frame[j]==page[i]){
                found=j;
                break;
            }
        }

        if(found!=-1){
            hit++;
            printf("Page %d ->hit\n",page[i]);
        }

        else{
            int idx=-1;
            for(int j=0;j<f;j++){
                if(frame[j]==-1){
                    idx=j;
                    break;
                }
            }

            if(idx==-1){
                int max=ref[0];
                idx=0;
                for(int j=1;j<f;j++){
                    if(ref[j]>max){
                        max=ref[j];
                        idx=j;
                    }
                }
            }
            frame[idx]=page[i];
            fault++;
            found=idx;
            printf("Page %d -> FAULT\n",page[i]);
        }
        for(int j=0;j<f;j++){
            ref[j]>>=1;
        }
        ref[found]|=128;
    }

    printf("\nTotal hits = %d", hit);
    printf("\nTotal faults = %d", fault);
    return 0;
}

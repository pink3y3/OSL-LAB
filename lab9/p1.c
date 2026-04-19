#include<stdio.h>

void first_fit(int nh, int hole_size[], int np, int process_size[]){
    int allocation[np];

    for(int i=0;i<np;i++){
        allocation[i]=-1;
    }

    for(int i=0;i<np;i++){
        for(int j=0;j<nh;j++){
            if(hole_size[j]>=process_size[i]){
                allocation[i]=j;
                hole_size[j]-=process_size[i];
                break;
            }
        }
    }
    printf("\nFirst-fit allocation");
    for(int i=0;i<np;i++){
        if(allocation[i]!=-1)
            printf("\nProcess %d (%d K) allocates hole %d",i,process_size[i],allocation[i]);
        else
            printf("\nProcess %d (%d K) not allocated\n",i,process_size[i]);
    }
}

void best_fit(int nh, int hole_size[], int np, int process_size[]){
    int allocation[np];

    for(int i=0;i<np;i++){
        allocation[i]=-1;
    }

    for(int i=0;i<np;i++){
        int best_idx=-1;
        for(int j=0;j<nh;j++){
            if(hole_size[j]>=process_size[i]){
                if(best_idx==-1 || hole_size[j]<hole_size[best_idx]){
                    best_idx=j;
                }
            }
        }
        if(best_idx!=-1){
            allocation[i]=best_idx;
            hole_size[best_idx]-=process_size[i];
        }
       
    }

    printf("\nBest-fit allocation");
    for(int i=0;i<np;i++){
        if(allocation[i]!=-1)
            printf("\nProcess %d (%d K) allocates hole %d",i,process_size[i],allocation[i]);
        else
            printf("\nProcess %d (%d K) not allocated\n",i,process_size[i]);
    }
}

void worst_fit(int nh, int hole_size[], int np, int process_size[]){
    int allocation[np];

    for(int i=0;i<np;i++){
        allocation[i]=-1;
    }

    for(int i=0;i<np;i++){
        int worst_idx=-1;

        for(int j=0;j<nh;j++){
            if(hole_size[j]>=process_size[i]){
                if(worst_idx==-1 || hole_size[j]>hole_size[worst_idx]){
                    worst_idx=j;
                }
            }
        }
        if(worst_idx!=-1){
            allocation[i]=worst_idx;
            hole_size[worst_idx]-=process_size[i];   
        }

    }

    printf("\nWorst-fit allocation\n ");
    for(int i=0;i<np;i++){
        if(allocation[i]!=-1)
            printf("\nProcess %d (%d K) allocates hole %d",i,process_size[i],allocation[i]);
        else
            printf("\nProcess %d (%d K) not allocated\n",i,process_size[i]);
    }
}

int main(){

    int nh,np;
    printf("\nenter number of holes and processes: ");
    scanf("%d%d",&nh,&np);

    int hole_size[nh],process_size[np];

    printf("\nenter hole sizes: ");
    for(int i=0;i<nh;i++){
        scanf("%d",&hole_size[i]);
    }

    printf("\nenter process sizes: ");
    for(int i=0;i<np;i++){
        scanf("%d",&process_size[i]);
    }

    int b1[nh], b2[nh], b3[nh];

    for(int i=0;i<nh;i++){
        b1[i]=hole_size[i];
        b2[i]=hole_size[i];
        b3[i]=hole_size[i];
    }

    first_fit(nh,b1,np,process_size);
    best_fit(nh,b2,np,process_size);
    worst_fit(nh,b3,np,process_size);

    return 0;
}
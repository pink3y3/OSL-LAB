#include<stdio.h>

int main(){
    int n;
    printf("enter number of segments: ");
    scanf("%d",&n);
    int base[n],limit[n];

    printf("\nenter base values: ");
    for(int i=0;i<n;i++){
        scanf("%d",&base[i]);
    }

    printf("\nenter limit registers: ");
    for(int i=0;i<n;i++){
        scanf("%d",&limit[i]);
    }

    int seg,offset;

    printf("enter segment number: ");
    scanf("%d", &seg);

    printf("enter offset: ");
    scanf("%d",&offset);

    if(offset>=limit[seg]){
        printf("\ninvalid address (offset exceeds limit)");
    }
    else{
        int physical=base[seg]+offset;
        printf("\nphysical address = %d",physical);
    }
    return 0;
}
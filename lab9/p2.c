#include<stdio.h>

int main(){
    int size,la;
    printf("enter page size: ");
    scanf("%d",&size);
    printf("enter logical address in bytes: ");
    scanf("%d",&la);
    printf("\nPage number in decimal: %d",la/size);
    printf("\nPage offset in decimal: %d",la%size);
    return 0;
}
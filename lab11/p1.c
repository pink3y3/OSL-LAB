#include<stdio.h>
#include<stdlib.h>

#define disk_size 199

void fcfs(int n, int arr[], int head){
    int tot=0;
    printf("\nFCFS: %d", head);

    for(int i=0;i<n;i++){
        tot+=abs(head-arr[i]);
        head=arr[i];
        printf(" -> %d",head);
    }

    printf("\nFCFS Total: %d\n",tot);
}

void sstf(int n, int arr[], int head){
    int visited[n];
    for(int i=0;i<n;i++) visited[i]=0;

    int tot=0;
    printf("\nSSTF: %d", head);

    for(int i=0;i<n;i++){
        int min_index=-1, min_dist=999999;

        for(int j=0;j<n;j++){
            if(!visited[j]){
                int dist = abs(head-arr[j]);
                if(dist < min_dist){
                    min_dist = dist;
                    min_index = j;
                }
            }
        }

        visited[min_index]=1;
        tot+=min_dist;
        head=arr[min_index];
        printf(" -> %d",head);
    }

    printf("\nSSTF Total: %d\n", tot);
}

void sort(int n, int arr[], int sorted[]){
    for(int i=0;i<n;i++) sorted[i]=arr[i];

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(sorted[j] > sorted[j+1]){
                int temp=sorted[j];
                sorted[j]=sorted[j+1];
                sorted[j+1]=temp;
            }
        }
    }
}

void scan(int n, int arr[], int head){
    int sorted[n];
    sort(n, arr, sorted);

    int pos=0;
    while(pos<n && sorted[pos] < head) pos++;

    int tot=0;
    printf("\nSCAN: %d", head);

    for(int i=pos;i<n;i++){
        tot+=abs(head-sorted[i]);
        head=sorted[i];
        printf(" -> %d",head);
    }

    tot+=abs(disk_size-head);
    head = disk_size;

    for(int i=pos-1;i>=0;i--){
        tot+=abs(head-sorted[i]);
        head=sorted[i];
        printf(" -> %d",head);
    }

    printf("\nSCAN Total: %d\n", tot);
}

void c_scan(int n, int arr[], int head){
    int sorted[n];
    sort(n, arr, sorted);

    int pos=0;
    while(pos<n && sorted[pos] < head) pos++;

    int tot=0;
    printf("\nC-SCAN: %d", head);

    for(int i=pos;i<n;i++){
        tot+=abs(head-sorted[i]);
        head=sorted[i];
        printf(" -> %d",head);
    }

    tot+=abs(disk_size-head);
    head = disk_size;

    tot += disk_size;
    head = 0;
    printf(" -> 0");

    for(int i=0;i<pos;i++){
        tot+=abs(head-sorted[i]);
        head=sorted[i];
        printf(" -> %d",head);
    }

    printf("\nC-SCAN Total: %d\n", tot);
}

void look(int n, int arr[], int head){
    int sorted[n];
    sort(n, arr, sorted);

    int pos=0;
    while(pos<n && sorted[pos] < head) pos++;

    int tot=0;
    printf("\nLOOK: %d", head);

    for(int i=pos;i<n;i++){
        tot+=abs(head-sorted[i]);
        head=sorted[i];
        printf(" -> %d",head);
    }

    for(int i=pos-1;i>=0;i--){
        tot+=abs(head-sorted[i]);
        head=sorted[i];
        printf(" -> %d",head);
    }

    printf("\nLOOK Total: %d\n", tot);
}

void c_look(int n, int arr[], int head){
    int sorted[n];
    sort(n, arr, sorted);

    int pos=0;
    while(pos<n && sorted[pos] < head) pos++;

    int tot=0;
    printf("\nC-LOOK: %d", head);

    for(int i=pos;i<n;i++){
        tot+=abs(head-sorted[i]);
        head=sorted[i];
        printf(" -> %d",head);
    }

    if(pos > 0){
        tot+=abs(head-sorted[0]);
        head=sorted[0];
        printf(" -> %d",head);

        for(int i=1;i<pos;i++){
            tot+=abs(head-sorted[i]);
            head=sorted[i];
            printf(" -> %d",head);
        }
    }

    printf("\nC-LOOK Total: %d\n", tot);
}

int main(){
    int n, head;

    printf("Enter number of service requests: ");
    scanf("%d",&n);

    int arr[n];

    printf("Enter service requests: ");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    printf("Enter head position: ");
    scanf("%d",&head);

    fcfs(n,arr,head);
    sstf(n,arr,head);
    scan(n,arr,head);
    c_scan(n,arr,head);
    look(n,arr,head);
    c_look(n,arr,head);

    return 0;
}
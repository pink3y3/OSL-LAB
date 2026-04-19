#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main(){
    int numbers[4],fd;
    const char *fifo_name="myfifo";

    mkfifo(fifo_name,0666);

    printf("\nenter 4 integers to send: ");
    for(int i=0;i<4;i++){
        scanf("%d",&numbers[i]);
    }

    fd=open(fifo_name,O_WRONLY);
    write(fd,numbers,sizeof(numbers));
    close(fd);

    printf("\nproducer: data sent to FIFO");
    return 0;
}
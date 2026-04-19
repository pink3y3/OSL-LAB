#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
    int fd;
    const char *fifo_name="myfifo";
    int numbers[4];

    fd=open(fifo_name,O_RDONLY);
    read(fd,numbers,sizeof(numbers));
    close(fd);

    printf("consumerL data received from fifo");
    for(int i=0;i<4;i++){
        printf("%d ",numbers[i]);
    }
    printf("\n");
    unlink(fifo_name);
    return 0;
}
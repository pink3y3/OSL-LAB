#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>

struct msg_buffer {
    long messageType;   // must be long
    int users;          // number of users
    int hour;           // observed hour
    int minute;         // observed minute
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate unique key
    key = ftok("msgqueuefile", 65);

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1) {
        perror("msgget");
        exit(1);
    }

    while(1) {
        // For demonstration, we input manually
        printf("Enter number of users: ");
        scanf("%d", &message.users);

        // Get current time
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        message.hour = t->tm_hour;
        message.minute = t->tm_min;

        message.messageType = 1; // can be any number

        // Send message to queue
        if(msgsnd(msgid, &message, sizeof(message)-sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        printf("Message sent: %d users at %02d:%02d\n", message.users, message.hour, message.minute);

        printf("Waiting 10 minutes for next observation...\n");
        sleep(600); // 600 seconds = 10 minutes
    }

    return 0;
}
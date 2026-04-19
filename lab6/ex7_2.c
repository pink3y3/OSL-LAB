#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long messageType;
    int users;
    int hour;
    int minute;
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    int total_users[24] = {0};
    int counts[24] = {0};

    // Generate the same key
    key = ftok("msgqueuefile", 65);

    // Access message queue
    msgid = msgget(key, 0666);
    if(msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Reading messages from queue...\n");

    while(1) {
        // Receive message
        if(msgrcv(msgid, &message, sizeof(message)-sizeof(long), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        int h = message.hour;
        total_users[h] += message.users;
        counts[h]++;

        printf("Received: %d users at %02d:%02d\n", message.users, message.hour, message.minute);

        // Compute hourly average
        printf("Current hourly averages:\n");
        for(int i=0; i<24; i++) {
            if(counts[i] > 0)
                printf("Hour %02d: %.2f users\n", i, (float)total_users[i]/counts[i]);
        }
        printf("-------------------------------------\n");
    }

    // Optional: remove queue
    // msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
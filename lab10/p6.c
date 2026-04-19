//enhances clock algorithm (RM model)

#include <stdio.h>

#define MAX 50

typedef struct {
    int page;
    int R;
    int M;
} Frame;

int main() {
    int pages[MAX], n, f;
    Frame frames[MAX];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(int i = 0; i < f; i++) {
        frames[i].page = -1;
        frames[i].R = 0;
        frames[i].M = 0;
    }

    int pointer = 0;
    int pageFaults = 0;

    for(int i = 0; i < n; i++) {
        int found = 0;

        // check if page exists
        for(int j = 0; j < f; j++) {
            if(frames[j].page == pages[i]) {
                frames[j].R = 1;
                found = 1;
                break;
            }
        }

        if(!found) {
            pageFaults++;

            while(1) {
                if(frames[pointer].R == 0 && frames[pointer].M == 0) {
                    break;
                }
                else if(frames[pointer].R == 0 && frames[pointer].M == 1) {
                    break;
                }
                else {
                    frames[pointer].R = 0;
                }

                pointer = (pointer + 1) % f;
            }

            // replace page
            frames[pointer].page = pages[i];
            frames[pointer].R = 1;
            frames[pointer].M = 0; // assume clean new page

            pointer = (pointer + 1) % f;
        }

        printf("\nFrames: ");
        for(int j = 0; j < f; j++)
            printf("%d ", frames[j].page);
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}
#include <stdio.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

int frames[MAX_FRAMES];
int freq[MAX_FRAMES];
int time[MAX_FRAMES];
int counter = 0;
int faults = 0;


void initializeFrames(int f) {
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }
}


int findPage(int page, int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}


int findLFU(int f) {
    int minFreq = freq[0];
    int pos = 0;

    for (int i = 1; i < f; i++) {
        if (freq[i] < minFreq) {
            minFreq = freq[i];
            pos = i;
        } else if (freq[i] == minFreq) {
            if (time[i] < time[pos]) {
                pos = i;
            }
        }
    }
    return pos;
}

void displayTable(int page, int f, int hit) {
    printf("%d\t", page);
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf("-\t");
        else
            printf("%d\t", frames[i]);
    }
    printf("%s\n", hit ? "Hit" : "Fault");
}

int main() {
    int pages[MAX_PAGES];
    int n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    initializeFrames(f);

    printf("\nPage\t");
    for (int i = 0; i < f; i++)
        printf("Frame%d\t", i + 1);
    printf("Status\n");

  
    for (int i = 0; i < n; i++) {
        counter++;
        int pos = findPage(pages[i], f);

        if (pos != -1) {
            freq[pos]++;
            displayTable(pages[i], f, 1);
        } else {
            int replaceIndex = -1;

            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            if (replaceIndex == -1)
                replaceIndex = findLFU(f);

            frames[replaceIndex] = pages[i];
            freq[replaceIndex] = 1;
            time[replaceIndex] = counter;
            faults++;

            displayTable(pages[i], f, 0);
        }
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 20

// Function prototypes
void LRU(int pages[], int numPages, int numFrames);
void FCFS(int pages[], int numPages, int numFrames);
void Optimal(int pages[], int numPages, int numFrames);

int main() {
    int pages[MAX_PAGES];
    int numPages, numFrames;
    
    // Take input for number of pages and number of frames
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);
    
    printf("Enter the page reference string: \n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Perform LRU page replacement
    printf("\nLRU (Least Recently Used) Page Replacement:\n");
    LRU(pages, numPages, numFrames);

    // Perform FCFS page replacement
    printf("\nFCFS (First-Come, First-Served) Page Replacement:\n");
    FCFS(pages, numPages, numFrames);

    // Perform Optimal page replacement
    printf("\nOptimal Page Replacement:\n");
    Optimal(pages, numPages, numFrames);

    return 0;
}

// Function to simulate LRU page replacement
void LRU(int pages[], int numPages, int numFrames) {
    int frames[numFrames];
    int time[numFrames]; // Store the last used time for each frame
    int faults = 0, timeCounter = 0;

    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
        time[i] = -1;   // Initialize time for all frames
    }

    for (int i = 0; i < numPages; i++) {
        int page = pages[i];
        int found = 0;
        
        // Check if the page is already in the frames
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                found = 1;
                time[j] = timeCounter++;
                break;
            }
        }

        // If the page is not found, page fault occurs
        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < numFrames; j++) {
                if (time[j] < time[lruIndex]) {
                    lruIndex = j;
                }
            }

            // Replace the least recently used page
            frames[lruIndex] = page;
            time[lruIndex] = timeCounter++;
            faults++;
        }

        printf("Page %d: ", page);
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("LRU page faults: %d\n", faults);
}

// Function to simulate FCFS page replacement
void FCFS(int pages[], int numPages, int numFrames) {
    int frames[numFrames];
    int faults = 0;
    int index = 0;

    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
    }

    for (int i = 0; i < numPages; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in the frames
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found, page fault occurs
        if (!found) {
            frames[index] = page;
            index = (index + 1) % numFrames;
            faults++;
        }

        printf("Page %d: ", page);
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("FCFS page faults: %d\n", faults);
}

// Function to simulate Optimal page replacement
void Optimal(int pages[], int numPages, int numFrames) {
    int frames[numFrames];
    int faults = 0;

    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
    }

    for (int i = 0; i < numPages; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in the frames
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found, page fault occurs
        if (!found) {
            // Find the page to replace using Optimal strategy
            int farthest = -1;
            int replaceIndex = -1;
            for (int j = 0; j < numFrames; j++) {
                int k;
                for (k = i + 1; k < numPages; k++) {
                    if (pages[k] == frames[j]) {
                        break;
                    }
                }
                if (k == numPages) {
                    replaceIndex = j;
                    break;
                }
                if (k > farthest) {
                    farthest = k;
                    replaceIndex = j;
                }
            }

            frames[replaceIndex] = page;
            faults++;
        }

        printf("Page %d: ", page);
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("Optimal page faults: %d\n", faults);
}

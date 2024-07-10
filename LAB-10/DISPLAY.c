#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_FRAMES 4

// Function to check if a page is present in memory
bool isInMemory(int page, int frames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to display the current state of frames in memory
void displayFrames(int frames[], int numFrames) {
    printf("Current state of frames: ");
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (i < numFrames) {
            printf("[%d] ", frames[i]);
        } else {
            printf("[ ] ");
        }
    }
    printf("\n");
}

// FIFO page replacement algorithm
void fifo(int pages[], int numPages) {
    int frames[MAX_FRAMES] = {-1};
    int numFrames = 0;
    int pageFaults = 0;
    int nextReplaceIndex = 0;

    for (int i = 0; i < numPages; i++) {
        int currentPage = pages[i];

        if (!isInMemory(currentPage, frames, numFrames)) {
            if (numFrames < MAX_FRAMES) {
                frames[numFrames++] = currentPage;
            } else {
                frames[nextReplaceIndex] = currentPage;
                nextReplaceIndex = (nextReplaceIndex + 1) % MAX_FRAMES;
            }
            pageFaults++;
            displayFrames(frames, numFrames);
        } else {
            printf("Page %d already in memory.\n", currentPage);
            displayFrames(frames, numFrames);
        }
    }

    printf("Total page faults (FIFO): %d\n", pageFaults);
}

// OPTIMAL page replacement algorithm
void optimal(int pages[], int numPages) {
    int frames[MAX_FRAMES] = {-1};
    int numFrames = 0;
    int pageFaults = 0;

    for (int i = 0; i < numPages; i++) {
        int currentPage = pages[i];

        if (!isInMemory(currentPage, frames, numFrames)) {
            if (numFrames < MAX_FRAMES) {
                frames[numFrames++] = currentPage;
            } else {
                int farthest = -1;
                int replaceIndex = -1;
                for (int j = 0; j < MAX_FRAMES; j++) {
                    int futureIndex = INT_MAX;
                    for (int k = i + 1; k < numPages; k++) {
                        if (frames[j] == pages[k]) {
                            futureIndex = k;
                            break;
                        }
                    }
                    if (futureIndex == INT_MAX) {
                        replaceIndex = j;
                        break;
                    }
                    if (futureIndex > farthest) {
                        farthest = futureIndex;
                        replaceIndex = j;
                    }
                }
                frames[replaceIndex] = currentPage;
            }
            pageFaults++;
            displayFrames(frames, numFrames);
        } else {
            printf("Page %d already in memory.\n", currentPage);
            displayFrames(frames, numFrames);
        }
    }

    printf("Total page faults (OPTIMAL): %d\n", pageFaults);
}

// LRU page replacement algorithm
void lru(int pages[], int numPages) {
    int frames[MAX_FRAMES] = {-1};
    int numFrames = 0;
    int pageFaults = 0;
    int counter = 0;
    int lastUsed[MAX_FRAMES] = {0};

    for (int i = 0; i < numPages; i++) {
        int currentPage = pages[i];
        int frameIndex = -1;

        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == currentPage) {
                frameIndex = j;
                break;
            }
        }

        if (frameIndex == -1) {
            if (numFrames < MAX_FRAMES) {
                frames[numFrames] = currentPage;
                lastUsed[numFrames++] = counter;
            } else {
                int replaceIndex = 0;
                for (int j = 1; j < MAX_FRAMES; j++) {
                    if (lastUsed[j] < lastUsed[replaceIndex]) {
                        replaceIndex = j;
                    }
                }
                frames[replaceIndex] = currentPage;
                lastUsed[replaceIndex] = counter;
            }
            pageFaults++;
            displayFrames(frames, numFrames);
        } else {
            lastUsed[frameIndex] = counter;
            printf("Page %d already in memory.\n", currentPage);
            displayFrames(frames, numFrames);
        }

        counter++;
    }

    printf("Total page faults (LRU): %d\n", pageFaults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int numPages = sizeof(pages) / sizeof(pages[0]);

    printf("FIFO Page Replacement Algorithm:\n");
    fifo(pages, numPages);

    printf("\nOPTIMAL Page Replacement Algorithm:\n");
    optimal(pages, numPages);

    printf("\nLRU Page Replacement Algorithm:\n");
    lru(pages, numPages);

    return 0;
}

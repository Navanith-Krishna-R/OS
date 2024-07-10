#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

void lru(int pages[], int n, int capacity) {
    int frame[MAX_FRAMES];
    int frame_used[MAX_FRAMES];
    int page_faults = 0;
    int used_time = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
        frame_used[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                frame_used[j] = used_time++;
                break;
            }
        }
        if (j == capacity) {
            int replace_page = 0;
            for (int k = 1; k < capacity; k++) {
                if (frame_used[k] < frame_used[replace_page]) {
                    replace_page = k;
                }
            }
            frame[replace_page] = pages[i];
            frame_used[replace_page] = used_time++;
            page_faults++;
        }

        printf("After inserting %d: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\nTotal page faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    printf("LRU Page Replacement Algorithm:\n");
    lru(pages, n, capacity);

    return 0;
}


#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

void optimal(int pages[], int n, int capacity) {
    int frame[MAX_FRAMES];
    bool frame_used[MAX_FRAMES];
    int page_faults = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
        frame_used[i] = false;
    }

    for (int i = 0; i < n; i++) {
        bool page_found = false;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                page_found = true;
                break;
            }
        }
        if (!page_found) {
            int farthest = i;
            int replace_page = -1;
            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replace_page = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    replace_page = j;
                    break;
                }
            }
            frame[replace_page] = pages[i];
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

    printf("Optimal Page Replacement Algorithm:\n");
    optimal(pages, n, capacity);

    return 0;
}


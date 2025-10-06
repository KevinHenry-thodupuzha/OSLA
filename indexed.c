#include <stdio.h>

int main() {
    int indexBlock[100], n, blockNumber;

    // Step 1: Ask user how many blocks to allocate
    printf("How many blocks to allocate? ");
    scanf("%d", &n);

    // Step 2: Allocate blocks
    for (int i = 0; i < n; i++) {
        printf("Enter block %d: ", i + 1);
        scanf("%d", &indexBlock[i]);
    }

    // Step 3: Show allocated blocks
    printf("\nBlocks allocated: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", indexBlock[i]);
    }
    printf("\n");

    // Step 4: Read blocks
    while (1) {
        printf("\nEnter block to read (-1 to stop): ");
        scanf("%d", &blockNumber);

        if (blockNumber == -1) {
            break; // exit loop
        }

        int found = 0;
        for (int i = 0; i < n; i++) {
            if (indexBlock[i] == blockNumber) {
                found = 1;
                break;
            }
        }

        if (found) {
            printf("Block %d is available.\n", blockNumber);
        } else {
            printf("Block %d is not allocated.\n", blockNumber);
        }
    }

    return 0;
}

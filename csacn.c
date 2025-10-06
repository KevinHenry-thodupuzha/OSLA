#include <stdio.h>
#include <stdlib.h> // for abs()

#define DISK_SIZE 200 // tracks are from 0 to 199

int main() {
    int n, start, direction;
    int totalMovement = 0;

    // Step 1: Input number of requests
    printf("Enter number of requests: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid number of requests!\n");
        return 0;
    }

    int requests[n];

    // Step 2: Input requests
    for (int i = 0; i < n; i++) {
        printf("Enter request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    // Step 3: Input starting position
    printf("Enter starting track: ");
    scanf("%d", &start);

    // Step 4: Input direction
    printf("Enter direction (1 = right →, 0 = left ←): ");
    scanf("%d", &direction);

    // Step 5: Sort the requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Start serving requests
    int head = start;
    printf("\nTrack execution order: %d", head);

    if (direction == 1) {
        // Move right first
        for (int i = 0; i < n; i++) {
            if (requests[i] >= start) {
                totalMovement += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }

        // Jump to beginning (circular move)
        if (head != DISK_SIZE - 1) {
            totalMovement += abs(head - (DISK_SIZE - 1)); // go to last track
            head = DISK_SIZE - 1;
            printf(" -> %d", head);
        }

        totalMovement += abs(head - 0); // jump from last track to 0
        head = 0;
        printf(" -> %d", head);

        // Serve remaining requests (those less than start)
        for (int i = 0; i < n; i++) {
            if (requests[i] < start) {
                totalMovement += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }
    } else {
        // Move left first
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= start) {
                totalMovement += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }

        // Jump to end (circular move)
        if (head != 0) {
            totalMovement += abs(head - 0); // go to first track
            head = 0;
            printf(" -> %d", head);
        }

        totalMovement += abs(head - (DISK_SIZE - 1)); // jump from 0 to last track
        head = DISK_SIZE - 1;
        printf(" -> %d", head);

        // Serve remaining requests (those greater than start)
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] > start) {
                totalMovement += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }
    }

    // Step 6: Print total movement
    printf("\nTotal head movement = %d\n", totalMovement);

    return 0;
}

#include <stdio.h>
#include <stdlib.h> // for abs()

int main() {
    int n, start;

    // Step 1: Get the number of disk requests
    printf("Enter number of requests: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid number of requests!\n");
        return 0;
    }

    int requests[n];

    // Step 2: Get the requested track numbers
    for (int i = 0; i < n; i++) {
        printf("Enter request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    // Step 3: Get starting track position
    printf("Enter start track: ");
    scanf("%d", &start);

    // Step 4: Show the execution order
    printf("\nTrack execution order: %d", start);
    int current = start;
    int totalMovement = 0;

    for (int i = 0; i < n; i++) {
        int distance = abs(current - requests[i]); // head movement
        totalMovement += distance;
        current = requests[i];
        printf(" -> %d", current); // print the next track in order
    }
    printf("\n");

    // Step 5: Show total head movement
    printf("Total head movement: %d\n", totalMovement);

    return 0;
}

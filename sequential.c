#include <stdio.h>
#include <string.h>

int main() {
    int n;  // number of files
    printf("Enter number of files: ");
    scanf("%d", &n);

    char filenames[n][50];   // array of file names
    int startblock[n];       // array for starting blocks
    int noofblocks[n];       // array for number of blocks

    // Input details of all files
    for(int i = 0; i < n; i++) {
        printf("\nEnter name of file %d: ", i+1);
        scanf("%s", filenames[i]);

        printf("Enter starting block of %s: ", filenames[i]);
        scanf("%d", &startblock[i]);

        printf("Enter number of blocks of %s: ", filenames[i]);
        scanf("%d", &noofblocks[i]);
    }

    // Display file details
    printf("\n--- File Allocation Table ---\n");
    printf("File\tStart\tBlocks\n");
    for(int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\n", filenames[i], startblock[i], noofblocks[i]);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, data;

    // Step 1: Define the structure for a block
    struct Block {
        int value;              // data part of the block
        struct Block* next;     // pointer to next block
    };

    struct Block* head = NULL;   // start of the list
    struct Block* tail = NULL;   // end of the list

    // Step 2: Ask user how many blocks
    printf("Enter the number of blocks: ");
    scanf("%d", &n);

    // Step 3: Create the linked list
    for (int i = 0; i < n; i++) {
        printf("Enter value for block %d: ", i + 1);
        scanf("%d", &data);

        // Create a new block
        struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
        newBlock->value = data;
        newBlock->next = NULL;

        // If the list is empty, newBlock is the head
        if (head == NULL) {
            head = newBlock;
            tail = newBlock;
        }
        // Otherwise, link at the end
        else {
            tail->next = newBlock;
            tail = newBlock;
        }
    }

    // Step 4: Print the linked list
    printf("Linked List: ");
    struct Block* temp = head;
    while (temp != NULL) {
        printf("%d", temp->value);
        if (temp->next != NULL) printf(" -> ");
        temp = temp->next;
    }
    printf(" -> NULL\n");

    // Step 5: Free the memory
    temp = head;
    while (temp != NULL) {
        struct Block* nextBlock = temp->next;
        free(temp);
        temp = nextBlock;
    }

    return 0;
}

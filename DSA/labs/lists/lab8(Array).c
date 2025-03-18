#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure for Array based List
typedef struct {
    int items[MAX_SIZE];
    int count;
} ArrayList;

// Initialize the list
void initializeArrayList(ArrayList *list) {
    list->count = 0;
}

// Check if the list is empty
int isEmpty(ArrayList *list) {
    return (list->count == 0);
}

// Check if the list is full
int isFull(ArrayList *list) {
    return (list->count == MAX_SIZE);
}

// Get the size of the list
int size(ArrayList *list) {
    return list->count;
}

// Insert an element at a specific position
int insertAt(ArrayList *list, int position, int value) {
    int i;
    
    // Check if the list is full
    if (isFull(list)) {
        printf("List is full. Cannot insert.\n");
        return 0;
    }
    
    // Check if the position is valid
    if (position < 0 || position > list->count) {
        printf("Invalid position.\n");
        return 0;
    }
    
    // Shift elements to make space for the new element
    for (i = list->count; i > position; i--) {
        list->items[i] = list->items[i - 1];
    }
    
    // Insert the new element
    list->items[position] = value;
    list->count++;
    
    return 1;
}

// Insert at the beginning
int insertAtBeginning(ArrayList *list, int value) {
    return insertAt(list, 0, value);
}

// Insert at the end
int insertAtEnd(ArrayList *list, int value) {
    return insertAt(list, list->count, value);
}

// Delete an element from a specific position
int deleteAt(ArrayList *list, int position) {
    int i;
    int deletedValue;
    
    // Check if the list is empty
    if (isEmpty(list)) {
        printf("List is empty. Cannot delete.\n");
        return -1;
    }
    
    // Check if the position is valid
    if (position < 0 || position >= list->count) {
        printf("Invalid position.\n");
        return -1;
    }
    
    // Save the value to be deleted
    deletedValue = list->items[position];
    
    // Shift elements to fill the gap
    for (i = position; i < list->count - 1; i++) {
        list->items[i] = list->items[i + 1];
    }
    
    list->count--;
    
    return deletedValue;
}

// Delete from the beginning
int deleteFromBeginning(ArrayList *list) {
    return deleteAt(list, 0);
}

// Delete from the end
int deleteFromEnd(ArrayList *list) {
    return deleteAt(list, list->count - 1);
}

// Search for an element in the list
int search(ArrayList *list, int value) {
    int i;
    
    for (i = 0; i < list->count; i++) {
        if (list->items[i] == value) {
            return i;  // Return the position if found
        }
    }
    
    return -1;  // Return -1 if not found
}

// Get value at specific position
int getAt(ArrayList *list, int position) {
    if (position < 0 || position >= list->count) {
        printf("Invalid position.\n");
        return -1;
    }
    
    return list->items[position];
}

// Display the list
void display(ArrayList *list) {
    int i;
    
    if (isEmpty(list)) {
        printf("List is empty.\n");
        return;
    }
    
    printf("List elements: ");
    for (i = 0; i < list->count; i++) {
        printf("%d ", list->items[i]);
    }
    printf("\n");
}

int main() {
    ArrayList list;
    int choice, position, value;
    
    initializeArrayList(&list);
    
    do {
        printf("\n\n------ ARRAY LIST OPERATIONS ------\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert at position\n");
        printf("4. Delete from beginning\n");
        printf("5. Delete from end\n");
        printf("6. Delete from position\n");
        printf("7. Search element\n");
        printf("8. Display list\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertAtBeginning(&list, value);
                break;
                
            case 2:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertAtEnd(&list, value);
                break;
                
            case 3:
                printf("Enter position: ");
                scanf("%d", &position);
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertAt(&list, position, value);
                break;
                
            case 4:
                value = deleteFromBeginning(&list);
                if (value != -1) {
                    printf("Deleted element: %d\n", value);
                }
                break;
                
            case 5:
                value = deleteFromEnd(&list);
                if (value != -1) {
                    printf("Deleted element: %d\n", value);
                }
                break;
                
            case 6:
                printf("Enter position: ");
                scanf("%d", &position);
                value = deleteAt(&list, position);
                if (value != -1) {
                    printf("Deleted element: %d\n", value);
                }
                break;
                
            case 7:
                printf("Enter value to search: ");
                scanf("%d", &value);
                position = search(&list, value);
                if (position != -1) {
                    printf("Element found at position: %d\n", position);
                } else {
                    printf("Element not found.\n");
                }
                break;
                
            case 8:
                display(&list);
                break;
                
            case 9:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 9);
    
    return 0;
}
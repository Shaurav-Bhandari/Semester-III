#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the Linked List
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Structure for Linked List
typedef struct {
    Node *head;
    int count;
} LinkedList;

// Initialize the list
void initializeLinkedList(LinkedList *list) {
    list->head = NULL;
    list->count = 0;
}

// Check if the list is empty
int isEmpty(LinkedList *list) {
    return (list->head == NULL);
}

// Get the size of the list
int size(LinkedList *list) {
    return list->count;
}

// Create a new node
Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Insert at the beginning
void insertAtBeginning(LinkedList *list, int value) {
    Node *newNode = createNode(value);
    
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
}

// Insert at the end
void insertAtEnd(LinkedList *list, int value) {
    Node *newNode = createNode(value);
    Node *temp;
    
    if (isEmpty(list)) {
        list->head = newNode;
    } else {
        temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    list->count++;
}

// Insert at a specific position
int insertAt(LinkedList *list, int position, int value) {
    Node *newNode, *temp;
    int i;
    
    // Check if the position is valid
    if (position < 0 || position > list->count) {
        printf("Invalid position.\n");
        return 0;
    }
    
    // Insert at the beginning if position is 0
    if (position == 0) {
        insertAtBeginning(list, value);
        return 1;
    }
    
    // Insert at a specific position
    newNode = createNode(value);
    temp = list->head;
    
    for (i = 0; i < position - 1; i++) {
        temp = temp->next;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
    list->count++;
    
    return 1;
}

// Delete from the beginning
int deleteFromBeginning(LinkedList *list) {
    Node *temp;
    int deletedValue;
    
    if (isEmpty(list)) {
        printf("List is empty. Cannot delete.\n");
        return -1;
    }
    
    temp = list->head;
    deletedValue = temp->data;
    list->head = temp->next;
    free(temp);
    list->count--;
    
    return deletedValue;
}

// Delete from the end
int deleteFromEnd(LinkedList *list) {
    Node *temp, *prev;
    int deletedValue;
    
    if (isEmpty(list)) {
        printf("List is empty. Cannot delete.\n");
        return -1;
    }
    
    // If only one node is present
    if (list->head->next == NULL) {
        temp = list->head;
        deletedValue = temp->data;
        list->head = NULL;
        free(temp);
        list->count--;
        return deletedValue;
    }
    
    // If more than one node is present
    temp = list->head;
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }
    
    deletedValue = temp->data;
    prev->next = NULL;
    free(temp);
    list->count--;
    
    return deletedValue;
}

// Delete from a specific position
int deleteAt(LinkedList *list, int position) {
    Node *temp, *prev;
    int i, deletedValue;
    
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
    
    // Delete from the beginning if position is 0
    if (position == 0) {
        return deleteFromBeginning(list);
    }
    
    // Delete from a specific position
    temp = list->head;
    
    for (i = 0; i < position; i++) {
        prev = temp;
        temp = temp->next;
    }
    
    deletedValue = temp->data;
    prev->next = temp->next;
    free(temp);
    list->count--;
    
    return deletedValue;
}

// Search for an element in the list
int search(LinkedList *list, int value) {
    Node *temp;
    int position = 0;
    
    temp = list->head;
    
    while (temp != NULL) {
        if (temp->data == value) {
            return position;  // Return the position if found
        }
        temp = temp->next;
        position++;
    }
    
    return -1;  // Return -1 if not found
}

// Get value at specific position
int getAt(LinkedList *list, int position) {
    Node *temp;
    int i;
    
    if (position < 0 || position >= list->count) {
        printf("Invalid position.\n");
        return -1;
    }
    
    temp = list->head;
    
    for (i = 0; i < position; i++) {
        temp = temp->next;
    }
    
    return temp->data;
}

// Display the list
void display(LinkedList *list) {
    Node *temp;
    
    if (isEmpty(list)) {
        printf("List is empty.\n");
        return;
    }
    
    printf("List elements: ");
    temp = list->head;
    
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    
    printf("\n");
}

// Free the memory allocated for the list
void destroyList(LinkedList *list) {
    Node *temp, *next;
    
    temp = list->head;
    
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    
    list->head = NULL;
    list->count = 0;
}

int main() {
    LinkedList list;
    int choice, position, value;
    
    initializeLinkedList(&list);
    
    do {
        printf("\n\n------ LINKED LIST OPERATIONS ------\n");
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
                destroyList(&list);
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 9);
    
    return 0;
}
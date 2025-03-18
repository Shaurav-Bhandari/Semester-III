// C Program to Implement Doubly Linked List
#include <stdio.h>
#include <stdlib.h>

// Defining a node
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new node with given value as data
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the beginning
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
}

// Function to insert a node at the end
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to insert a node at a specified position
void insertAtPosition(Node** head, int data, int position) {
    if (position < 1) {
        printf("Position should be >= 1.\n");
        return;
    }

    if (position == 1) {
        insertAtBeginning(head, data);
        return;
    }

    Node* newNode = createNode(data);
    Node* temp = *head;
    for (int i = 1; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position greater than the number of nodes. Adding at the end.\n");
        insertAtEnd(head, data);
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

// Function to delete a node from the beginning
void deleteAtBeginning(Node** head) {
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

// Function to delete a node from the end
void deleteAtEnd(Node** head) {
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }

    Node* temp = *head;
    if (temp->next == NULL) {
        *head = NULL;
        free(temp);
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
}

// Function to delete a node from a specified position
void deleteAtPosition(Node** head, int position) {
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }
    Node* temp = *head;
    if (position == 1) {
        deleteAtBeginning(head);
        return;
    }
    for (int i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position is greater than the number of nodes.\n");
        return;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    free(temp);
}

// Function to print the list in forward direction
void printListForward(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node* temp = head;
    printf("Forward List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to print the list in reverse direction
void printListReverse(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    printf("Reverse List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

// Main function
int main() {
    Node* head = NULL;
    int value, choice, position;

    while (1) {
        printf("\n*********** MENU *************\n");
        printf("1. Insert\n2. Delete\n3. Display\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to be inserted: ");
                scanf("%d", &value);
                printf("Select Insertion Position:\n1. At Beginning\n2. At End\n3. At Position\nEnter choice: ");
                int insertChoice;
                scanf("%d", &insertChoice);

                if (insertChoice == 1)
                    insertAtBeginning(&head, value);
                else if (insertChoice == 2)
                    insertAtEnd(&head, value);
                else if (insertChoice == 3) {
                    printf("Enter position: ");
                    scanf("%d", &position);
                    insertAtPosition(&head, value, position);
                } else
                    printf("Invalid insertion option!\n");
                break;

            case 2:
                printf("Select Deletion Position:\n1. At Beginning\n2. At End\n3. At Position\nEnter choice: ");
                int deleteChoice;
                scanf("%d", &deleteChoice);

                if (deleteChoice == 1)
                    deleteAtBeginning(&head);
                else if (deleteChoice == 2)
                    deleteAtEnd(&head);
                else if (deleteChoice == 3) {
                    printf("Enter position: ");
                    scanf("%d", &position);
                    deleteAtPosition(&head, position);
                } else
                    printf("Invalid deletion option!\n");
                break;

            case 3:
                printListForward(head);
                printListReverse(head);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice! Please select a valid option.\n");
        }
    }
    return 0;
}

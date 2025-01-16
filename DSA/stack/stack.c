#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct stack {
    char value[MAX];
    int top;
} myStack;

void makeStack(myStack *stack) {
    stack->top = -1;
}

int isStackFull(myStack *stack) {
    return stack->top == MAX - 1;
}

int isStackNull(myStack *stack) {
    return stack->top == -1;
}

int push(myStack *stack, char value) {
    if (isStackFull(stack)) {
        printf("Stack is full. Cannot push.\n");
        return 0;
    }
    stack->value[++stack->top] = value;
    return 1;
}

char pop(myStack *stack) {
    if (isStackNull(stack)) {
        printf("Stack is empty. Cannot pop.\n");
        return '\0';
    }
    return stack->value[stack->top--];
}

void printStack(myStack *stack) {
    if (isStackNull(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack contents: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%c ", stack->value[i]);
    }
    printf("\n");
}

int main() {
    int choice;
    char goAgain;
    myStack Stack;
    makeStack(&Stack);

    printf("Creating a new stack... Done.\n");
    do {
        printf("\nChoose an operation:\n1. Push\n2. Pop\n3. Print\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            char x;
            printf("Enter the element you'd like to push: ");
            scanf(" %c", &x); // Add a space before %c
            push(&Stack, x);
            break;
        }
        case 2: {
            char y = pop(&Stack);
            if (y != '\0') {
                printf("You popped: %c\n", y);
            }
            break;
        }
        case 3:
            printStack(&Stack);
            break;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }

        printf("Want to continue? (y/n): ");
        scanf(" %c", &goAgain); // Add a space before %c
    } while (goAgain == 'y');

    return 0;
}

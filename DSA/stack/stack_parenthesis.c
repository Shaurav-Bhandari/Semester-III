#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct stack
{
    char arr[MAX];
    int top;
} Stack;

// Initialize the stack
void initializeStack() {
    Stack.top = -1;
}

// Push an item onto the stack
void push(char item) {
    if (Stack.top == MAX - 1) {
        printf("Stack is full.\n");
        return;
    }
    Stack.top++;
    Stack.arr[Stack.top] = item;
}

// Pop an item from the stack
void pop() {
    if (Stack.top == -1) {
        printf("Stack is empty.\n");
        return;
    }
    Stack.top--;
}

// Check if two characters form a valid pair of parentheses
int checkpair(char val1, char val2) {
    return (val1 == '(' && val2 == ')');
}

// Check if the given expression has balanced parentheses
void checkBalance(char expr[], int len) {
    for (int i = 0; i < len; i++) {
        if (expr[i] == '(') {
            push(expr[i]);
        } else if (expr[i] == ')') {
            if (Stack.top == -1) {
                printf("Unbalanced: Extra closing parenthesis at index %d\n", i);
                return;
            } else if (checkpair(Stack.arr[Stack.top], expr[i])) {
                pop();
            } else {
                printf("Unbalanced: Mismatched parenthesis at index %d\n", i);
                return;
            }
        }
    }

    // Final check: If the stack is not empty, there are unmatched opening parentheses
    if (Stack.top != -1) {
        printf("Unbalanced: Extra opening parenthesis.\n");
    } else {
        printf("Parentheses are balanced.\n");
    }
}

int main() {
    char expression[MAX];
    printf("Enter an expression with parentheses: ");
    scanf("%s", expression);

    // Initialize the stack before usage
    initializeStack();

    // Check the balance of the parentheses
    checkBalance(expression, strlen(expression));

    return 0;
}

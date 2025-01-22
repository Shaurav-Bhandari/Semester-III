#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Stack structure
struct Stack {
    int top;
    char items[MAX_SIZE];
};

// Stack operations
void initialize(struct Stack *s) {
    s->top = -1;
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}

int isFull(struct Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(struct Stack *s, char value) {
    if (!isFull(s)) {
        s->items[++(s->top)] = value;
    } else {
        printf("Stack overflow\n");
        exit(1);
    }
}

char pop(struct Stack *s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

char peek(struct Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return '\0';
}

// Function to get operator precedence
int precedence(char oper) {
    switch (oper) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

// Function to check if character is operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to reverse string
void reverseString(char *str) {
    int length = strlen(str);
    int i, j;
    char temp;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// Function to convert infix to postfix
void infixToPostfix(char *infix, char *postfix) {
    struct Stack stack;
    initialize(&stack);
    
    int i, j = 0;
    char ch;
    
    for (i = 0; infix[i] != '\0'; i++) {
        ch = infix[i];
        
        if (isalnum(ch)) {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            push(&stack, ch);
        }
        else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            if (!isEmpty(&stack) && peek(&stack) == '(') {
                pop(&stack);  // Remove '('
            } else {
                printf("Mismatched parentheses\n");
                exit(1);
            }
        }
        else if (isOperator(ch)) {
            while (!isEmpty(&stack) && peek(&stack) != '(' && 
                   precedence(ch) <= precedence(peek(&stack))) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, ch);
        }
        // Skip whitespace
        else if (!isspace(ch)) {
            printf("Invalid character in expression\n");
            exit(1);
        }
    }
    
    while (!isEmpty(&stack)) {
        char top = pop(&stack);
        if (top == '(') {
            printf("Mismatched parentheses\n");
            exit(1);
        }
        postfix[j++] = top;
    }
    
    postfix[j] = '\0';
}

// Function to convert infix to prefix
void infixToPrefix(char *infix, char *prefix) {
    // First reverse the infix expression
    char revInfix[MAX_SIZE];
    strncpy(revInfix, infix, MAX_SIZE - 1);
    revInfix[MAX_SIZE - 1] = '\0';
    reverseString(revInfix);
    
    // Replace '(' with ')' and vice versa
    for (int i = 0; revInfix[i] != '\0'; i++) {
        if (revInfix[i] == '(')
            revInfix[i] = ')';
        else if (revInfix[i] == ')')
            revInfix[i] = '(';
    }
    
    // Convert to postfix
    char tempPostfix[MAX_SIZE];
    infixToPostfix(revInfix, tempPostfix);
    
    // Reverse the result to get prefix
    strncpy(prefix, tempPostfix, MAX_SIZE - 1);
    prefix[MAX_SIZE - 1] = '\0';
    reverseString(prefix);
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE], prefix[MAX_SIZE];
    
    printf("Enter infix expression: ");
    if (fgets(infix, MAX_SIZE, stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    // Remove newline if present
    size_t len = strlen(infix);
    if (len > 0 && infix[len-1] == '\n') {
        infix[len-1] = '\0';
    }
    
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    
    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);
    
    return 0;
}
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stack type
struct Stack {
    int top;
    unsigned capacity;
    double* array;
};

// Stack operations
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));

    if (!stack)
        return NULL;

    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (double*)malloc(stack->capacity * sizeof(double));

    if (!stack->array)
        return NULL;

    return stack;
}
int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}
double peek(struct Stack* stack)
{
    return stack->array[stack->top];
}
double pop(struct Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return 0; 
}
void push(struct Stack* stack, double op)
{
    stack->array[++stack->top] = op;
}
// Prefix evaluation
double evaluatePrefix(char* expr)
{
    struct Stack* stack = createStack(strlen(expr));
    int i;
    if (!stack)
        return -1;
    for (i = strlen(expr) - 1; i >= 0; i--) {
        if (expr[i] == ' ')
            continue;
        if (isdigit(expr[i])) {
            double num = 0;
            int factor = 1;

            // Read the complete number
            while (i >= 0 && isdigit(expr[i])) {
                num = (expr[i] - '0') * factor + num;
                factor *= 10;
                i--;
            }

            i++; 
            push(stack, num);
        } else {
            double operand1 = pop(stack);
            double operand2 = pop(stack);

            switch (expr[i]) {
            case '+':
                push(stack, operand1 + operand2);
                break;
            case '-':
                push(stack, operand1 - operand2);
                break;
            case '*':
                push(stack, operand1 * operand2);
                break;
            case '/':
                push(stack, operand1 / operand2);
                break;
            }
        }
    }

    double result = pop(stack);
    free(stack->array);
    free(stack);
    return result;
}
// Postfix evaluation
double evaluatePostfix(char* expr)
{
    struct Stack* stack = createStack(strlen(expr));
    int i;
    if (!stack)
        return -1;
    for (i = 0; expr[i]; i++) {
        if (expr[i] == ' ')
            continue;
        if (isdigit(expr[i])) {
            double num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }

            i--; 
            push(stack, num);
        } else {
            double operand2 = pop(stack);
            double operand1 = pop(stack);

            switch (expr[i]) {
            case '+':
                push(stack, operand1 + operand2);
                break;
            case '-':
                push(stack, operand1 - operand2);
                break;
            case '*':
                push(stack, operand1 * operand2);
                break;
            case '/':
                push(stack, operand1 / operand2);
                break;
            }
        }
    }

    double result = pop(stack);
    free(stack->array);
    free(stack);
    return result;
}
int main()
{
    char prefixExpr[] = "+ 9 * 12 6"; // Example prefix expression
    char postfixExpr[] = "12 6 * 9 +"; // Example postfix expression

    printf("Prefix Evaluation Result: %.2f\n", evaluatePrefix(prefixExpr));
    printf("Postfix Evaluation Result: %.2f\n", evaluatePostfix(postfixExpr));

    return 0;
}
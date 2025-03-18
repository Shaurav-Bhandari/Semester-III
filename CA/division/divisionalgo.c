#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function to convert decimal to binary string
char* decimalToBinary(unsigned int n, int* length) {
    if (n == 0) {
        char* binary = (char*)malloc(2);
        binary[0] = '0';
        binary[1] = '\0';
        *length = 1;
        return binary;
    }
    
    // Find number of bits needed
    int bits = (int)log2(n) + 1;
    *length = bits;
    
    // Allocate memory for binary string
    char* binary = (char*)malloc(bits + 1);
    binary[bits] = '\0';
    
    // Convert to binary
    for (int i = bits - 1; i >= 0; i--) {
        binary[bits - i - 1] = (n & (1 << i)) ? '1' : '0';
    }
    
    return binary;
}

// Function to convert binary string to decimal
unsigned int binaryToDecimal(const char* binary) {
    unsigned int decimal = 0;
    int length = strlen(binary);
    
    for (int i = 0; i < length; i++) {
        if (binary[i] == '1') {
            decimal += pow(2, length - i - 1);
        }
    }
    
    return decimal;
}

// Function to perform restoring division algorithm
void restoringDivision(unsigned int dividend, unsigned int divisor) {
    if (divisor == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return;
    }
    
    if (dividend < divisor) {
        printf("Quotient: 0 (Binary: 0)\n");
        printf("Remainder: %u (Binary: ", dividend);
        int lenD;
        char* binD = decimalToBinary(dividend, &lenD);
        printf("%s)\n", binD);
        free(binD);
        return;
    }
    
    // Convert to binary
    int lenA, lenB;
    char* binA = decimalToBinary(dividend, &lenA);
    char* binB = decimalToBinary(divisor, &lenB);
    
    printf("Dividend (A): %u (Binary: %s)\n", dividend, binA);
    printf("Divisor (B): %u (Binary: %s)\n", divisor, binB);
    printf("\nRestoring Division Algorithm Steps:\n");
    
    // Determine the number of bits in the quotient
    int n = lenA;
    int m = lenB;
    int quotientBits = n - m + 1;
    
    // Initialize A and Q
    char* A = (char*)malloc(n + 1);
    char* Q = (char*)malloc(quotientBits + 1);
    memset(A, '0', n);
    A[n] = '\0';
    memset(Q, '0', quotientBits);
    Q[quotientBits] = '\0';
    
    // Create a buffer for the padded divisor
    char* paddedB = (char*)malloc(n + 1);
    memset(paddedB, '0', n - m);
    strcpy(paddedB + (n - m), binB);
    paddedB[n] = '\0';
    
    // Create a buffer for the full dividend
    char* fullA = (char*)malloc(n + 1);
    strcpy(fullA, binA);
    fullA[n] = '\0';
    
    printf("\nInitial state:\n");
    printf("A: %s\n", A);
    printf("Q: %s\n", fullA);
    printf("B: %s\n", paddedB);
    
    // Perform division
    for (int i = 0; i < quotientBits; i++) {
        // Shift A and Q left by 1 bit
        for (int j = 0; j < n - 1; j++) {
            A[j] = A[j + 1];
        }
        A[n - 1] = fullA[i];
        
        printf("\nStep %d:\n", i + 1);
        printf("Shift left: A = %s, Q = %s\n", A, fullA + i + 1);
        
        // Subtract B from A
        int borrow = 0;
        char* tempA = (char*)malloc(n + 1);
        
        for (int j = n - 1; j >= 0; j--) {
            int bitA = A[j] - '0';
            int bitB = paddedB[j] - '0';
            int diff = bitA - bitB - borrow;
            
            if (diff < 0) {
                diff += 2;
                borrow = 1;
            } else {
                borrow = 0;
            }
            
            tempA[j] = diff + '0';
        }
        tempA[n] = '\0';
        
        printf("A - B = %s\n", tempA);
        
        // Check if A is negative (we use the borrow flag)
        if (borrow == 1) {
            // Restoring: A = A + B
            printf("A is negative, restoring A = A + B\n");
            int carry = 0;
            for (int j = n - 1; j >= 0; j--) {
                int bitA = tempA[j] - '0';
                int bitB = paddedB[j] - '0';
                int sum = bitA + bitB + carry;
                
                if (sum > 1) {
                    sum -= 2;
                    carry = 1;
                } else {
                    carry = 0;
                }
                
                A[j] = sum + '0';
            }
            Q[i] = '0';
        } else {
            // A is positive, keep the result
            strcpy(A, tempA);
            Q[i] = '1';
        }
        
        printf("A: %s, Q: %s\n", A, Q);
        free(tempA);
    }
    
    // Calculate the remainder (in A)
    unsigned int remainder = binaryToDecimal(A);
    unsigned int quotient = binaryToDecimal(Q);
    
    printf("\nFinal Result:\n");
    printf("Quotient: %u (Binary: %s)\n", quotient, Q);
    printf("Remainder: %u (Binary: %s)\n", remainder, A);
    
    printf("\nExpected outcome: %u ÷ %u = %u with remainder %u\n", 
           dividend, divisor, dividend / divisor, dividend % divisor);
    printf("Observed outcome: %u ÷ %u = %u with remainder %u\n", 
           dividend, divisor, quotient, remainder);
    
    // Free allocated memory
    free(binA);
    free(binB);
    free(A);
    free(Q);
    free(paddedB);
    free(fullA);
}

int main() {
    unsigned int dividend, divisor;
    
    printf("Restoring Division Algorithm for Unsigned Binary Numbers\n");
    printf("======================================================\n\n");
    
    printf("Enter dividend (decimal): ");
    scanf("%u", &dividend);
    
    printf("Enter divisor (decimal): ");
    scanf("%u", &divisor);
    
    restoringDivision(dividend, divisor);
    
    return 0;
}
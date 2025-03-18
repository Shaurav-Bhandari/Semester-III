#include <stdio.h>
#include <math.h>

#define SIZE 5

int a = 0, b = 0;
int anum[SIZE] = {0}, bnum[SIZE] = {0}, bcomp[SIZE] = {0};
int pro[SIZE] = {0}, anumcp[SIZE] = {0};

void binary() {
    int a1 = fabs(a), b1 = fabs(b);
    int i, carry = 1;
    
    for (i = 0; i < SIZE; i++) {
        anum[i] = a1 % 2;
        a1 /= 2;
        bnum[i] = b1 % 2;
        b1 /= 2;
        bcomp[i] = bnum[i] ? 0 : 1; // One's complement of B
    }
    
    // Compute two's complement of B
    for (i = 0; i < SIZE; i++) {
        int temp = bcomp[i] + carry;
        bcomp[i] = temp % 2;
        carry = temp / 2;
    }
    
    // Handle negative numbers
    if (a < 0) {
        carry = 1;
        for (i = 0; i < SIZE; i++) {
            int temp = !anum[i] + carry;
            anum[i] = temp % 2;
            carry = temp / 2;
        }
    }
    if (b < 0) {
        for (i = 0; i < SIZE; i++) {
            int temp = bnum[i];
            bnum[i] = bcomp[i];
            bcomp[i] = temp;
        }
    }
    
    // Copy anum for processing
    for (i = 0; i < SIZE; i++) {
        anumcp[i] = anum[i];
    }
}

void display_step(int step, int q, char operation) {
    int i;
    printf("\nStep %d: ", step);
    
    // Display operation performed
    if (operation == '0') {
        printf("A%d = Q%d, No addition, Arithmetic right shift", step-1, step-1);
    } else if (operation == '+') {
        printf("A%d = 1, Q%d = 0, Add B, Arithmetic right shift", step-1, step-1);
    } else if (operation == '-') {
        printf("A%d = 0, Q%d = 1, Add -B, Arithmetic right shift", step-1, step-1);
    }
    
    // Display current accumulator and Q register
    printf("\nAccumulator: ");
    for (i = SIZE - 1; i >= 0; i--) {
        printf("%d", pro[i]);
    }
    
    printf(" | Q Register: ");
    for (i = SIZE - 1; i >= 0; i--) {
        printf("%d", anumcp[i]);
    }
    
    printf(" | Q-1: %d", q);
    printf("\n");
}

void add(int num[]) {
    int i, carry = 0;
    for (i = 0; i < SIZE; i++) {
        int temp = pro[i] + num[i] + carry;
        pro[i] = temp % 2;
        carry = temp / 2;
    }
}

void arshift() {
    int i;
    int temp = pro[SIZE - 1]; // Keep MSB of A for sign extension
    int temp2 = pro[0];       // LSB of A goes to MSB of Q
    
    for (i = 1; i < SIZE; i++) {
        pro[i - 1] = pro[i];
    }
    pro[SIZE - 1] = temp;     // Sign extension
    
    for (i = 1; i < SIZE; i++) {
        anumcp[i - 1] = anumcp[i];
    }
    anumcp[SIZE - 1] = temp2; // LSB of A becomes MSB of Q
}

int main() {
    int i, q = 0, step = 1;
    char operation;
    
    printf("\n\t\tBOOTH'S MULTIPLICATION ALGORITHM");
    printf("\nEnter two numbers to multiply (both < 16):");
    
    do {
        printf("\nEnter A: ");
        scanf("%d", &a);
        printf("Enter B: ");
        scanf("%d", &b);
    } while (a >= 16 || b >= 16);
    
    printf("\nExpected product = %d", a * b);
    binary();
    
    printf("\n\nBinary Equivalents are:");
    printf("\nA = ");
    for (i = SIZE - 1; i >= 0; i--) {
        printf("%d", anum[i]);
    }
    printf("\nB = ");
    for (i = SIZE - 1; i >= 0; i--) {
        printf("%d", bnum[i]);
    }
    printf("\n-B = ");
    for (i = SIZE - 1; i >= 0; i--) {
        printf("%d", bcomp[i]);
    }
    
    printf("\n\nInitial values:");
    printf("\nAccumulator: ");
    for (i = SIZE - 1; i >= 0; i--) {
        printf("%d", pro[i]);
    }
    printf(" | Q Register: ");
    for (i = SIZE - 1; i >= 0; i--) {
        printf("%d", anumcp[i]);
    }
    printf(" | Q-1: %d", q);
    printf("\n\nBooth's Algorithm Steps:");
    
    for (i = 0; i < SIZE; i++) {
        // Decide operation based on current bit and previous bit
        if (anumcp[0] == q) {
            operation = '0'; // No addition, just shift
        } else if (anumcp[0] == 1 && q == 0) {
            operation = '-'; // Add -B (B's 2's complement)
            add(bcomp);
        } else { // anumcp[0] == 0 && q == 1
            operation = '+'; // Add B
            add(bnum);
        }
        
        // Display step before shift
        display_step(step, q, operation);
        
        // Perform arithmetic right shift
        arshift();
        q = anumcp[0];
        step++;
        
        // Add a pause for user to observe each step
        printf("Press Enter to continue to the next step...");
        getchar(); // Consume newline from previous input
        getchar(); // Wait for Enter key
    }
    
    printf("\nFinal Result:");
    printf("\nBinary Product = ");
    for (i = SIZE - 1; i >= 0; i--) {
        printf("%d", pro[i]);
    }
    for (i = SIZE - 1; i >= 0; i--) {
        printf("%d", anumcp[i]);
    }
    
    // Calculate decimal equivalent of binary product
    int decimal_product = 0, power = 1;
    for (i = 0; i < SIZE; i++) {
        decimal_product += anumcp[i] * power;
        power *= 2;
    }
    for (i = 0; i < SIZE; i++) {
        decimal_product += pro[i] * power;
        power *= 2;
    }
    
    // Handle negative results correctly
    if (pro[SIZE-1] == 1) {
        // This is a negative number in 2's complement
        decimal_product = decimal_product - (power / 2);
    }
    
    printf("\nDecimal Product = %d", decimal_product);
    printf("\nExpected Product = %d\n", a * b);
    
    return 0;
}
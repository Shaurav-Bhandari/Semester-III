#include <stdio.h>

// 1. Factorial
int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// 2. Fibonacci Sequence
int fibonacci(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 3. Greatest Common Divisor (Euclidean algorithm)
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// 4. Tower of Hanoi
void tower_of_hanoi(int n, char source, char auxiliary, char target) {
    if (n == 1) {
        printf("Move disk 1 from rod %c to rod %c\n", source, target);
        return;
    }
    tower_of_hanoi(n - 1, source, target, auxiliary);
    printf("Move disk %d from rod %c to rod %c\n", n, source, target);
    tower_of_hanoi(n - 1, auxiliary, source, target);
}

// Main function to demonstrate the algorithms
int main() {
    // Test factorial
    printf("Factorial of 5: %d\n", factorial(5));
    // Test fibonacci
    printf("7th Fibonacci number: %d\n", fibonacci(7));
    // Test GCD
    printf("GCD of 48 and 18: %d\n", gcd(48, 18));
    // Test Tower of Hanoi
    printf("Tower of Hanoi solution for 3 disks:\n");
    tower_of_hanoi(3, 'A', 'B', 'C');
    
    return 0;
}
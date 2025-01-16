#include <stdio.h>
#include <math.h>

// Function g(x) rearranged from f(x) = cos(x)-3x+1 = 0
// to fixed point form x = g(x) = (cos(x)+1)/3
double g(double x) {
    return cos(x) - 3 * x + 1;
}

// Fixed Point Iteration implementation
double fixedPointIteration(double x0, double epsilon, int maxIterations) {
    double x1;
    int iteration = 0;
    
    printf("Starting Fixed Point Iteration with x0 = %.6f\n", x0);
    
    do {
        x1 = g(x0);  // Calculate next approximation
        
        // Print current approximation
        printf("Iteration %d: x = %.6f, |x1-x0| = %.6f\n", 
               iteration + 1, x1, fabs(x1 - x0));
        
        // Check if maximum iterations reached
        if (iteration >= maxIterations) {
            printf("Warning: Maximum iterations reached\n");
            return x1;
        }
        
        x0 = x1;     // Update for next iteration
        iteration++;
        
    } while (fabs(x1 - x0) >= epsilon); // Continue until desired accuracy is reached
    
    return x1;
}

// Original function f(x) = cos(x)-3x+1 to verify the root
double f(double x) {
    return cos(x) - 3 * x + 1;
}

int main() {
    double x0 = 0.5;         // Initial guess
    double epsilon = 1e-6;    // Desired accuracy
    int maxIterations = 100;  // Maximum number of iterations
    
    printf("Solving equation: cos(x) - 3x + 1 = 0\n");
    printf("Using Fixed Point Iteration method\n\n");
    
    double root = fixedPointIteration(x0, epsilon, maxIterations);
    
    printf("\nApproximate root: %.8f\n", root);
    printf("f(root) = %.8f\n", f(root));
    printf("\nThis code is run by Shaurav Bhandari");
    
    return 0;
}
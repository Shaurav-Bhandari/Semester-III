#include <stdio.h>
#include <math.h>

// Function to find the root of
double f(double x) {
    // Example function: x^3 - 2x - 5
    return pow(x, 3) - 2 * x - 5;
}

// g(x) is the function rearranged to fixed point form
// For example, if f(x) = x^3 - 2x - 5, we can rearrange to
// x = (x^3 - 5)/2 or other suitable forms
double g(double x) {
    return (pow(x, 3) - 5) / 2;
}

// Fixed Point Iteration implementation
double fixedPointMethod(double x0, double epsilon, int maxIterations) {
    double x1;
    int iteration = 0;
    
    do {
        x1 = g(x0);  // Calculate next approximation
        
        // Print current approximation
        printf("Iteration %d: x = %.4f, f(x) = %.4f\n", iteration + 1, x1, f(x1));
        
        // Check if maximum iterations reached
        if (iteration >= maxIterations) {
            printf("Warning: Maximum iterations reached\n");
            return x1;
        }
        
        // Update for next iteration
        x0 = x1;
        iteration++;
        
    } while (fabs(f(x1)) >= epsilon); // Continue until desired accuracy is reached
    
    return x1;
}

int main() {
    double x0;         // Initial guess
    double epsilon;    // Desired accuracy
    int maxIterations; // Maximum number of iterations
    
    printf("Enter initial guess x0:\n");
    scanf("%lf", &x0);
    
    printf("Enter the tolerance:\n");
    scanf("%lf", &epsilon);
    
    printf("Enter maximum iterations:\n");
    scanf("%d", &maxIterations);
    
    printf("Initial guess: x0 = %.2f\n", x0);
    
    double root = fixedPointMethod(x0, epsilon, maxIterations);
    
    printf("\nApproximate root: %.8f\n", root);
    printf("f(root) = %.8f\n", f(root));
    printf("\nThis code is run by Shaurav Bhandari");
    
    return 0;
}
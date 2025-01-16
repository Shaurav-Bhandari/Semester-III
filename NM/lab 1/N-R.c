#include <stdio.h>
#include <math.h>

// Function to find the root of
double f(double x) {
    // Example function: x^2 - 4
    // Change this function as needed
    return 3 * x - cos(x) - 1;
}

// Derivative of the function
double df(double x) {
    // Derivative of x^2 - 4 is 2x
    // Change this derivative as needed
    return 3 + sin(x);
}

// Newton-Raphson method implementation
double newtonRaphson(double x0, double epsilon, int maxIterations) {
    double x = x0;
    double h;
    int iteration = 0;
    
    do {
        // Check if derivative is zero to avoid division by zero
        if (fabs(df(x)) < epsilon) {
            printf("Error: Derivative too close to zero\n");
            return x;
        }
        
        // Calculate h = f(x)/f'(x)
        h = f(x) / df(x);
        
        // Update x
        x = x - h;
        
        // Increment iteration count
        iteration++;
        
        // Print current approximation
        printf("Iteration %d: x = %.6f\n", iteration, x);
        
        // Check if maximum iterations reached
        if (iteration >= maxIterations) {
            printf("Warning: Maximum iterations reached\n");
            return x;
        }
        
    } while (fabs(h) >= epsilon); // Continue until desired accuracy is reached
    
    return x;
}

int main() {
    double initial_guess, epsilon;
    int maxIterations;

    // Input values
    printf("Enter the initial guess:\n");
    scanf("%lf", &initial_guess);

    printf("Enter the tolerance:\n");
    scanf("%lf", &epsilon);

    printf("Enter the maximum number of iterations:\n");
    scanf("%d", &maxIterations);
    
    double root = newtonRaphson(initial_guess, epsilon, maxIterations);
    
    printf("\nApproximate root: %.8f\n", root);
    printf("f(root) = %.8f\n", f(root));
    printf("\nThis code is run by Shaurav Bhandari");
    
    return 0;
}
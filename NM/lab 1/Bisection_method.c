#include <stdio.h>
#include <math.h>

// Define the function for which we want to find the root
double f(double x) {
    return cos(x) - x * exp(x); // Example: f(x) = x^2 - 4
}

// Bisection method function
void bisection(double a, double b, double tolerance, int maxIterations) {
    double c; // Midpoint
    int iteration = 0;

    // Check if initial interval is valid
    if (f(a) * f(b) >= 0) {
        printf("The function has the same sign at a and b. The method cannot proceed.\n");
        return;
    }

    printf("Iteration\t a\t\t b\t\t c\t\t f(c)\n");
    do {
        // Calculate the midpoint
        c = (a + b) / 2.0;

        // Print the current iteration values
        printf("%d\t\t %.6f\t %.6f\t %.6f\t %.6f\n", iteration, a, b, c, f(c));

        // Check if the midpoint is a root
        if (fabs(f(c)) <= tolerance) {
            printf("\nRoot found: %.6f\n", c);
            return;
        }

        // Update the interval
        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }

        iteration++;

    } while (iteration < maxIterations && fabs(b - a) > tolerance);

    // Print the final result
    printf("\nAfter %d iterations, the best estimate of the root is: %.6f\n", iteration, c);
}

int main() {
    double a, b, tolerance;
    int maxIterations;

    // Input values
    printf("Enter the interval [a, b]:\n");
    scanf("%lf %lf", &a, &b);

    printf("Enter the tolerance:\n");
    scanf("%lf", &tolerance);

    printf("Enter the maximum number of iterations:\n");
    scanf("%d", &maxIterations);

    // Call the bisection method
    bisection(a, b, tolerance, maxIterations);
    printf("\nThis code is run by Shaurav Bhandari\n");

    return 0;
}

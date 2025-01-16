#include <stdio.h>

int main() {
    float x_values[10], y_values[10], divided_differences[10];
    float interpolation_point, result, num_points, term = 1, cumulative_sum = 0;
    int i, j = 1;

    // Input the number of observations
    printf("\nEnter the number of observations:\n");
    scanf("%f", &num_points);

    // Input the x-values
    printf("Enter the x-values:\n");
    for (i = 1; i <= num_points; i++) {
        scanf("%f", &x_values[i]);
    }

    // Input the corresponding y-values
    printf("\nEnter the corresponding y-values:\n");
    for (i = 1; i <= num_points; i++) {
        scanf("%f", &y_values[i]);
    }

    // Initialize the result with the first y-value
    result = y_values[1];

    // Input the interpolation point
    printf("Enter the value of k for f(k) to evaluate:\n");
    scanf("%f", &interpolation_point);

    // Perform Newton's Divided Difference Interpolation
    do {
        for (i = 1; i <= num_points - 1; i++) {
            divided_differences[i] = 
                (y_values[i + 1] - y_values[i]) / (x_values[i + j] - x_values[i]);
            y_values[i] = divided_differences[i];
        }

        // Calculate the product term for the interpolation
        term = 1;
        for (i = 1; i <= j; i++) {
            term *= (interpolation_point - x_values[i]);
        }

        // Accumulate the result using the current term
        cumulative_sum += y_values[1] * term;
        num_points--;
        j++;
    } while (num_points != 1);

    // Final result of interpolation
    result += cumulative_sum;
    printf("\nf(%f) = %f\n", interpolation_point, result);
    printf("This program is run by Shaurav Bhandari...");
    return 0;
}

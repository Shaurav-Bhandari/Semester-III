#include <stdio.h>

int main() {
    int num_points, i;
    float sum_x = 0, sum_x_squared = 0, sum_y = 0, sum_xy = 0;
    float intercept, slope;

    /* Input */
    printf("Enter the number of data points:\n");
    scanf("%d", &num_points);

    float x_values[num_points], y_values[num_points];

    printf("Enter the data points:\n");
    for (i = 1; i <= num_points; i++) {
        printf("x[%d] = ", i);
        scanf("%f", &x_values[i]);
        printf("y[%d] = ", i);
        scanf("%f", &y_values[i]);
    }

    /* Calculating required sums */
    for (i = 1; i <= num_points; i++) {
        sum_x += x_values[i];
        sum_x_squared += x_values[i] * x_values[i];
        sum_y += y_values[i];
        sum_xy += x_values[i] * y_values[i];
    }

    /* Calculating slope (b) and intercept (a) */
    slope = (num_points * sum_xy - sum_x * sum_y) / (num_points * sum_x_squared - sum_x * sum_x);
    intercept = (sum_y - slope * sum_x) / num_points;

    /* Displaying results */
    printf("Values are: intercept (a) = %.2f and slope (b) = %.2f\n", intercept, slope);
    printf("Equation of best fit is: y = %.2f + %.2fx\n", intercept, slope);
    printf("This program is run by Shaurav Bhandari...");
    return 0;
}

#include <stdio.h>

int main()
{
    float x_values[100], y_values[100], interpolation_point, interpolated_value = 0, term;
    int i, j, num_points;

    /* Input Section */
    printf("Enter the number of data points: ");
    scanf("%d", &num_points);
    printf("Enter the data points:\n");
    
    for (i = 1; i <= num_points; i++)
    {
        printf("x[%d] = ", i);
        scanf("%f", &x_values[i]);
        printf("y[%d] = ", i);
        scanf("%f", &y_values[i]);
    }
    
    printf("Enter the interpolation point: ");
    scanf("%f", &interpolation_point);

    /* Implementing Lagrange Interpolation */
    for (i = 1; i <= num_points; i++)
    {
        term = 1;
        for (j = 1; j <= num_points; j++)
        {
            if (i != j)
            {
                term *= (interpolation_point - x_values[j]) / (x_values[i] - x_values[j]);
            }
        }
        interpolated_value += term * y_values[i];
    }

    printf("The interpolated value at %.3f is %.3f.\n", interpolation_point, interpolated_value);
    printf("This code is run by Shaurav Bhandari...");
    return 0;
}

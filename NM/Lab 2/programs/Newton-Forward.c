#include <stdio.h>

int main() {
    // Variables for array sizes and loop counters
    int numPoints;         // Number of data points
    int i, j, k;          // Loop counters
    
    // Arrays to store data points and differences
    float xValues[20];             // X coordinates
    float yValues[20];             // Y coordinates
    float differences[20][20];     // Table for forward differences
    
    // Variables for interpolation
    float xTarget;                 // X value for which we want to find Y
    float parameter;               // (xTarget - x0) / h
    float stepSize;                // Distance between consecutive x values
    float numerator = 1.0;         // Numerator of the term in Newton's formula
    float denominator = 1.0;       // Denominator of the term in Newton's formula
    float yResult;                 // Final interpolated y value
    
    // Input number of data points
    printf("\nEnter the number of data points: ");
    scanf("%d", &numPoints);
    
    // Input data points (x,y coordinates)
    printf("\nEnter the values in form x,y:\n");
    for (i = 0; i <= numPoints - 1; i++) {
        scanf("%f %f", &xValues[i], &yValues[i]);
    }
    
    // Input the x value for interpolation
    printf("\nEnter the value of x for which you want to find y: \n");
    scanf("%f", &xTarget);
    
    // Calculate step size (assuming uniform spacing)
    stepSize = xValues[1] - xValues[0];
    
    // Calculate first order differences
    for (i = 0; i < numPoints; i++) {
        differences[i][1] = yValues[i+1] - yValues[i];
    }
    
    // Calculate higher order differences
    for (j = 2; j < numPoints; j++) {
        for (i = 0; i < numPoints - j; i++) {
            differences[i][j] = differences[i+1][j-1] - differences[i][j-1];
        }
    }
    
    // Calculate interpolation parameter
    parameter = (xTarget - xValues[0]) / stepSize;
    
    // Initialize result with y0
    yResult = yValues[0];
    
    // Apply Newton's Forward Interpolation Formula
    for (k = 1; k < numPoints; k++) {
        // Update numerator: p * (p-1) * (p-2) * ...
        numerator *= (parameter - k + 1);
        
        // Update denominator: 1 * 2 * 3 * ...
        denominator *= k;
        
        // Add term to result: (numerator/denominator) * difference
        yResult += (numerator/denominator) * differences[0][k];
    }
    
    // Display result
    printf("\nWhen x = %f, corresponding y = %f\n", xTarget, yResult);
    printf("This code is run By Shaurav Bhandari...");
    return 0;
}
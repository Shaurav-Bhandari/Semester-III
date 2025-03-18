#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void forward(float x[20], float y[20][20], int n);
void backward(float x[20], float y[20][20], int n);
int main(int argc, char const *argv[])
{
    float x[20], y[20][20];
    int i, j, n; 
    int n = 4;
    printf("enter the number of data points(<20): ");
    scanf("%d", &n);
    printf("Enter the data: ");
    for (int i = 0; i < n; i++)
    {
        printf("x[%d] = ", i);
        scanf("%f", &x[i]);
        printf("x[%d]", i);
        scanf("%f",&y[i][0]);
    }
    
    
    return 0;
}

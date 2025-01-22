// {rogram to implement Dynamic memory allocation} 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int n, *arr, i, sum = 0;
    printf("Enter the number of elements:\n");
    scanf("%d", &n);
    arr = (int*)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation faled...");
    }
    printf("Enter %d number of elements...\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    printf("The sum of the numbers entered by you is: %d", sum);
    
    
    
    return 0;
}

// {rogram to implement Dynamic memory allocation} 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int n, *arr, i, sum;
    printf("Enter the number of elements:\n");
    scanf("%d", &n);
    arr = (int*)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation faled...");
    }
    
    return 0;
}

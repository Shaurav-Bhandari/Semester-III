#include <stdio.h>

void selectionSort(int arr[], int size)
{
    int minimum, temp;
    minimum = 0;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if (arr[j]< arr[minimum])
            {
                minimum = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minimum];
        arr[minimum] = temp;
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {7,4,10,8,3,1};
    int size = sizeof(arr)/sizeof(int);
    printf("Before sorting, array is: \n");
    for (int i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n\nAfter sorting, Array = \n");
    selectionSort(arr, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }
    return 0;
}

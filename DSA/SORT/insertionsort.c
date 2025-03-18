#include <stdio.h>
#include <stdlib.h>


//function to insertion sort
void insertionSort(int arr[], int size){
    //Declare variables
    int i, hole, temp;
    //i for loop indexing. hole for storing the first element of the unsorted subarray, temp for the last element of sorted array
    for ( i = 1; i <= size-1; i++)//Run the loop
    {
        temp = arr[i];//set the last element of the sorted array to the temp
        hole =  i;//index of the first element of the unsorted subarray is set to hole
        //run the loop to sort
        while (hole >= 0 && arr[hole - 1] > arr[hole])
        {
            arr[hole] = arr[hole -1];
            hole--;
        }
        arr[hole] = temp;        
    }
    
};

int main(int argc, char const *argv[])
{
    int arr[] = {3, 5, 4, 11, 9};
    int size = sizeof(arr)/sizeof(int);
    printf("Array before sorting: \n");
    for (int  i = 0; i < size; i++)
    {
        printf("\t%d", arr[i]);
    }
    insertionSort(arr, size);
    printf("\nAfter sorting:\n");
    for (int i = 0; i < size; i++)
    {
        printf("\t%d", arr[i]);
    }
    return 0;
}

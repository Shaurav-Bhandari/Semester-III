#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 1. Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        // Last i elements are already in place
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
        }
    }
}

// 2. Insertion Sort
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        
        // Move elements that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 3. Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Select the rightmost element as pivot
    int i = (low - 1);      // Index of smaller element
    
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;  // Increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is the partitioning index
        int pi = partition(arr, low, high);
        
        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 4. Merge Sort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    // Create temp arrays
    int L[n1], R[n2];
    
    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    // Merge the temp arrays back into arr[l..r]
    i = 0;  // Initial index of first subarray
    j = 0;  // Initial index of second subarray
    k = l;  // Initial index of merged subarray
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;
        
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        
        merge(arr, l, m, r);
    }
}

// 5. Shell Sort
void shellSort(int arr[], int n) {
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is gap sorted
        for (int i = gap; i < n; i += 1) {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];
            
            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
                
            // put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
}

// 6. Heap Sort
// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int arr[], int n, int i) {
    int largest = i;    // Initialize largest as root
    int l = 2 * i + 1;  // left = 2*i + 1
    int r = 2 * i + 2;  // right = 2*i + 2
    
    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;
    
    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;
    
    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);
        
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Test function
void testSortingAlgorithms() {
    int arr_size = 10;
    int test_arr[10];
    
    // Test each algorithm
    printf("Testing sorting algorithms with random arrays of size %d:\n\n", arr_size);
    
    // Seed for random numbers
    srand(time(NULL));
    
    // Test Bubble Sort
    for (int i = 0; i < arr_size; i++)
        test_arr[i] = rand() % 100;
    printf("Bubble Sort:\nOriginal Array: ");
    printArray(test_arr, arr_size);
    bubbleSort(test_arr, arr_size);
    printf("Sorted Array: ");
    printArray(test_arr, arr_size);
    printf("\n");
    
    // Test Insertion Sort
    for (int i = 0; i < arr_size; i++)
        test_arr[i] = rand() % 100;
    printf("Insertion Sort:\nOriginal Array: ");
    printArray(test_arr, arr_size);
    insertionSort(test_arr, arr_size);
    printf("Sorted Array: ");
    printArray(test_arr, arr_size);
    printf("\n");
    
    // Test Quick Sort
    for (int i = 0; i < arr_size; i++)
        test_arr[i] = rand() % 100;
    printf("Quick Sort:\nOriginal Array: ");
    printArray(test_arr, arr_size);
    quickSort(test_arr, 0, arr_size - 1);
    printf("Sorted Array: ");
    printArray(test_arr, arr_size);
    printf("\n");
    
    // Test Merge Sort
    for (int i = 0; i < arr_size; i++)
        test_arr[i] = rand() % 100;
    printf("Merge Sort:\nOriginal Array: ");
    printArray(test_arr, arr_size);
    mergeSort(test_arr, 0, arr_size - 1);
    printf("Sorted Array: ");
    printArray(test_arr, arr_size);
    printf("\n");
    
    // Test Shell Sort
    for (int i = 0; i < arr_size; i++)
        test_arr[i] = rand() % 100;
    printf("Shell Sort:\nOriginal Array: ");
    printArray(test_arr, arr_size);
    shellSort(test_arr, arr_size);
    printf("Sorted Array: ");
    printArray(test_arr, arr_size);
    printf("\n");
    
    // Test Heap Sort
    for (int i = 0; i < arr_size; i++)
        test_arr[i] = rand() % 100;
    printf("Heap Sort:\nOriginal Array: ");
    printArray(test_arr, arr_size);
    heapSort(test_arr, arr_size);
    printf("Sorted Array: ");
    printArray(test_arr, arr_size);
    printf("\n");
}

int main() {
    testSortingAlgorithms();
    return 0;
}
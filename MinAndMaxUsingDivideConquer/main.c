#include <stdio.h>
#include <stdlib.h>

// A structure to return multiple values from a function
struct Pair {
    int min;
    int max;
};

// Function to find the minimum and maximum using divide and conquer
struct Pair findMinMax(int arr[], int low, int high) {
    struct Pair minmax, left, right;
    int mid;

    // Base case: If the array has only one element
    if (low == high) {
        minmax.min = arr[low];
        minmax.max = arr[low];
        return minmax;
    }

    // If the array has two elements
    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            minmax.min = arr[low];
            minmax.max = arr[high];
        } else {
            minmax.min = arr[high];
            minmax.max = arr[low];
        }
        return minmax;
    }

    // If the array has more than two elements
    mid = (low + high) / 2;

    // Recursively find the min and max in the left and right halves
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    // Combine the results
    minmax.min = (left.min < right.min) ? left.min : right.min;
    minmax.max = (left.max > right.max) ? left.max : right.max;

    return minmax;
}
int main()
{
    int n;
    printf("Enter the size of the array : ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array : \n");
    for(int i=0;i<n;i++){
        printf("Enter arr[%d] : ", i);
        scanf("%d", &arr[i]);
    }
    struct Pair minmax = findMinMax(arr, 0, n-1);
    printf("Minimum element is %d\n", minmax.min);
    printf("Maximum element is %d\n", minmax.max);

    return 0;
}

#include <stdio.h>


void displayArray(int arr[],int size){

    for(int i=0;i<size;i++){
        printf("element in array[%d] : %d \n", i, arr[i]);
    }

}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void partition(int arr[],int low, int high){
    int pivot = arr[high];
    int i = (low-1);

    for(int j=low;j<= high;j++){
        if(arr[j]<pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[high]);
    return (i+1);
}

void QuickSort(int arr[],int low, int high){
    if(low<high){
        int pivotIndex = partition(arr,low,high);

        QuickSort(arr,low,pivotIndex-1);
        QuickSort(arr,pivotIndex+1,high);
    }
}
int main()
{

    int size;
    printf("Ënter the size of the array : ");
    scanf("%d", &size);

    int array[size];

    printf("Enter the %d elements into the array : \n", size);

    for(int i=0;i<size;i++){
     printf("Enter array[%d] element : ", i);
     scanf("%d", &array[i]);
    }

    printf("Unsorted array : \n");
    displayArray(array,size);


    QuickSort(array,0,size-1);

    printf("Sorted array : \n");
    displayArray(array, size);

    return 0;
}

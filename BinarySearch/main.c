#include <stdio.h>

void BubbleSort(int arr[],int size){
  for(int i=0;i<size-1;i++){
    for(int j=0;j<size-i-1;j++){
        if(arr[j]>arr[j+1]){
            int temp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = temp;
        }
    }
  }
}

int BinarySearch(int arr[], int size, int key){
    int low = 0;
    int high = size-1;

    while(low<=high){
        int mid = low + (high-low)/2;

        if(arr[mid]==key){
            return mid;
        }else if(arr[mid]<key){
            low = mid+1;
        }else{
            high = mid-1;
        }
    }
    return -1;
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

    BubbleSort(array,size);

    printf("Sorted array : ");
    for(int i=0;i<size;i++){
        printf("%d\t", array[i]);
    }
    printf("\n");

    int key;
    printf("Enter the element to be searched : ");
    scanf("%d", &key);


    int result = BinarySearch(array, size, key);

    if(result != -1){
        printf("%d is found at %d.\n", key, result);
    }else{
        printf("%d is not found in the array.\n", key);
    }

    return 0;
}

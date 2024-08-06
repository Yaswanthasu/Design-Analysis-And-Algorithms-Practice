#include <stdio.h>


void displayArray(int arr[],int size){

    for(int i=0;i<size;i++){
        printf("element in array[%d] : %d \n", i, arr[i]);
    }

}

void Merge(int arr[], int low, int mid, int high){

    int i,j,k;
    int n1 = mid-low+1;
    int n2 = high-mid;

    int L[n1],R[n2];

    for(i=0;i<n1;i++){
        L[i] = arr[low+i];
    }
    for(j=0;j<n2;j++){
        R[j] = arr[mid+1+j];
    }
    i=0;
    j=0;
    k=low;

    while(i<n1 && j<n2){
        if(L[i]<=R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j<n2){
        arr[k] = R[j];
        j++;
        k++;
    }


}
void MergeSort(int arr[], int low, int high){

    if(low<high){

        int mid = low + (high-low)/2;
        MergeSort(arr,low,mid);
        MergeSort(arr,mid+1,high);

        Merge(arr, low, mid, high);
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


    MergeSort(array,0,size-1);

    printf("Sorted array : \n");
    displayArray(array, size);

    return 0;
}


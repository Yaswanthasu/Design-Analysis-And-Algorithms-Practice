#include <stdio.h>

int knapsack_recursive(int weights[], int values[], int n, int capacity) {
    // Base case: No items left or capacity is 0
    if (n == 0 || capacity == 0) {
        return 0;
    }

    // If the weight of the nth item is more than capacity, it cannot be included
    if (weights[n-1] > capacity) {
        return knapsack_recursive(weights, values, n-1, capacity);
    } else {
        // Return the maximum of including the nth item or not including it
        int include_item = values[n-1] + knapsack_recursive(weights, values, n-1, capacity - weights[n-1]);
        int exclude_item = knapsack_recursive(weights, values, n-1, capacity);
        return (include_item > exclude_item) ? include_item : exclude_item;
    }
}

int main() {
    int n;
    printf("Enter the number of weights : ");
    scanf("%d", &n);
    int weights[n],values[n];
    for(int i=0;i<n;i++){
        printf("Enter the weight and it's corresponding value : ");
        scanf("%d %d", &weights[i], &values[i]);
    }

    int capacity;
    printf("Enter the capacity of the knapsack : ");
    scanf("%d", &capacity);

    printf("Maximum value in Knapsack = %d\n", knapsack_recursive(weights, values, n, capacity));
    return 0;
}

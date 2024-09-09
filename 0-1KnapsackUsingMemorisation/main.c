#include <stdio.h>

#define MAX_ITEMS 100
#define MAX_CAPACITY 100

int memo[MAX_ITEMS+1][MAX_CAPACITY+1];

int knapsack_memoization(int weights[], int values[], int n, int capacity) {
    // Base case
    if (n == 0 || capacity == 0) {
        return 0;
    }

    // Check if the value is already computed
    if (memo[n][capacity] != -1) {
        return memo[n][capacity];
    }

    // If the weight of the nth item is more than capacity, it cannot be included
    if (weights[n-1] > capacity) {
        return memo[n][capacity] = knapsack_memoization(weights, values, n-1, capacity);
    } else {
        // Max value of including or excluding the item
        int include_item = values[n-1] + knapsack_memoization(weights, values, n-1, capacity - weights[n-1]);
        int exclude_item = knapsack_memoization(weights, values, n-1, capacity);
        return memo[n][capacity] = (include_item > exclude_item) ? include_item : exclude_item;
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

    // Initialize memo table
    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            memo[i][w] = -1;
        }
    }

    printf("Maximum value in Knapsack = %d\n", knapsack_memoization(weights, values, n, capacity));
    return 0;
}

#include <stdio.h>

int knapsack_tabulation(int weights[], int values[], int n, int capacity) {
    int dp[n+1][capacity+1];

    // Initialize all dp values to 0
    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i-1] <= w) {
                // Max value of including or excluding the item
                dp[i][w] = (values[i-1] + dp[i-1][w - weights[i-1]] > dp[i-1][w]) ?values[i-1] + dp[i-1][w - weights[i-1]] : dp[i-1][w];                 
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    return dp[n][capacity];
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
    printf("Maximum value in Knapsack = %d\n", knapsack_tabulation(weights, values, n, capacity));
    return 0;
}

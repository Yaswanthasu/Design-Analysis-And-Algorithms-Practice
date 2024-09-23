#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int set[MAX];
int subsetSum[MAX][MAX];

bool isSubsetSum(int n, int sum) {
    if (sum == 0)
        return true;
    if (n == 0)
        return false;

    if (subsetSum[n][sum] != -1)
        return subsetSum[n][sum];

    if (set[n - 1] > sum) {
        subsetSum[n][sum] = isSubsetSum(n - 1, sum);
        return subsetSum[n][sum];
    }

    subsetSum[n][sum] = isSubsetSum(n - 1, sum) || isSubsetSum(n - 1, sum - set[n - 1]);
    return subsetSum[n][sum];
}

int main() {
    int n, sum;

    printf("Enter the number of elements in the set: ");
    scanf("%d", &n);

    printf("Enter the elements of the set:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &set[i]);

    printf("Enter the sum to be found: ");
    scanf("%d", &sum);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= sum; j++)
            subsetSum[i][j] = -1;

    if (isSubsetSum(n, sum))
        printf("Subset with given sum exists.\n");
    else
        printf("No subset with given sum exists.\n");

    printf("\nFinal table values:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= sum; j++) {
            if (subsetSum[i][j] == -1) {
                printf("-1 ");
            } else {
                printf("%d ", subsetSum[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}

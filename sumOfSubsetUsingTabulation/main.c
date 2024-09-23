#include <stdio.h>
#include <stdbool.h>

bool isSubsetSum(int set[], int n, int sum)
{
    bool subset[n + 1][sum + 1];

    // Initialize the subset table
    for (int i = 0; i <= n; i++)
        subset[i][0] = true;

    for (int i = 1; i <= sum; i++)
        subset[0][i] = false;

    // Fill the subset table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1])
                subset[i][j] = subset[i - 1][j];
            else
                subset[i][j] = subset[i - 1][j] || subset[i - 1][j - set[i - 1]];
        }
    }

    // Print the final subset table
    printf("\nFinal subset table:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= sum; j++) {
            printf("%d ", subset[i][j]);
        }
        printf("\n");
    }

    return subset[n][sum];
}

int main()
{
    int n;
    printf("Enter the number of elements in the set: ");
    scanf("%d", &n);
    int set[n];
    printf("Enter the numbers in the set: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &set[i]);
    }

    int sum;
    printf("Enter the target sum : ");
    scanf("%d", &sum);
    if (isSubsetSum(set, n, sum))
        printf("\nFound a subset with the given sum\n");
    else
        printf("\nNo subset with the given sum\n");

    return 0;
}

#include <stdio.h>

int isSubsetSum(int nums[], int target_sum, int n) {
    // Base Cases
    if (target_sum == 0)
        return 1; // True
    if (n == 0)
        return 0; // False

    // If the last element is greater than the target sum, ignore it
    if (nums[n-1] > target_sum)
        return isSubsetSum(nums, target_sum, n-1);

    // Check if the target sum can be obtained by either including or excluding the last element
    return isSubsetSum(nums, target_sum - nums[n-1], n-1) || isSubsetSum(nums, target_sum, n-1);
}

int main() {
    int n, target_sum;

    // Taking input for the number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int nums[n];

    // Taking input for the elements
    printf("Enter the numbers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    // Taking input for the target sum
    printf("Enter the target sum: ");
    scanf("%d", &target_sum);

    if (isSubsetSum(nums, target_sum, n))
        printf("Found a subset with the target sum\n");
    else
        printf("No subset with the target sum exists\n");

    return 0;
}

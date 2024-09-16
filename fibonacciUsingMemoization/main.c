#include <stdio.h>

#define MAX 100  // Define a maximum limit for Fibonacci calculation

int memo[MAX];

// Function to initialize the memo array
void initializeMemo() {
    for (int i = 0; i < MAX; i++) {
        memo[i] = -1;  // -1 indicates that the value has not been computed yet
    }
}

int fibonacci(int n) {
    // Check if the result is already in the memo array
    if (memo[n] != -1) {
        return memo[n];
    }

    // Base cases
    if (n <= 1) {
        memo[n] = n;
        return n;
    }

    // Recursive case with memoization
    memo[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return memo[n];
}

int main() {
    int n = 10;  // You can change this value to compute different Fibonacci numbers
    initializeMemo();
    printf("Fibonacci(%d) = %d\n", n, fibonacci(n));
    return 0;
}

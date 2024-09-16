#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;

    // Create an array to store Fibonacci numbers
    int fib[n + 1];
    fib[0] = 0;
    fib[1] = 1;

    // Build the table in a bottom-up manner
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

int main() {
    int n = 10;  // You can change this value to compute different Fibonacci numbers
    printf("Fibonacci(%d) = %d\n", n, fibonacci(n));
    return 0;
}

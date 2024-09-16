#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n = 10;  // You can change this value to compute different Fibonacci numbers
    printf("Fibonacci(%d) = %d\n", n, fibonacci(n));
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
typedef struct {
    int index;
    int weight;
    int value;
    double ratio; // Value-to-weight ratio
} Item;

// Function to compare two items based on their value-to-weight ratio
int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    return (itemB->ratio > itemA->ratio) - (itemB->ratio < itemA->ratio);
}

// Function to solve fractional knapsack problem
double fractionalKnapsack(int capacity, Item items[], int n) {
    qsort(items, n, sizeof(Item), compare);

    double totalValue = 0.0;
    for (int i = 0; i < n; i++) {
        if (capacity == 0)
            break;
        int takeWeight = items[i].weight < capacity ? items[i].weight : capacity;
        totalValue += takeWeight * items[i].ratio;
        capacity -= takeWeight;
    }
    return totalValue;
}

int main() {
    int n, capacity;

    // Input number of items
    printf("Enter the number of items: ");
    scanf("%d", &n);

    // Allocate memory for items
    Item *items = (Item *)malloc(n * sizeof(Item));

    // Input values and weights for each item
    for (int i = 0; i < n; i++) {
        printf("Enter value and weight for item %d: ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
        items[i].index = i; // Optional: for tracking the original order
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    // Input capacity of the knapsack
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    // Calculate maximum value
    double maxValue = fractionalKnapsack(capacity, items, n);
    printf("Maximum value in fractional knapsack = %.2f\n", maxValue);

    // Free allocated memory
    free(items);

    return 0;
}

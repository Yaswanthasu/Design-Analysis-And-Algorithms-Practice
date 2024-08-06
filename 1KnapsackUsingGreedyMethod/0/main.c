#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
typedef struct {
    int value;
    int weight;
    double ratio;
} Item;

// Function to compare two items based on their value-to-weight ratio
int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemA->ratio < itemB->ratio) return 1;
    if (itemA->ratio > itemB->ratio) return -1;
    return 0;
}

// Greedy algorithm for 0/1 knapsack problem
int knapsack(int W, Item items[], int n) {
    // Sort items by value-to-weight ratio
    qsort(items, n, sizeof(Item), compare);

    int currentWeight = 0;
    int finalValue = 0;

    // Iterate over sorted items
    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= W) {
            // If the item can be added, add it
            currentWeight += items[i].weight;
            finalValue += items[i].value;
        }
    }

    return finalValue;
}

int main() {
    int n, W;

    // Input number of items
    printf("Enter the number of items: ");
    scanf("%d", &n);

    // Allocate memory for items
    Item *items = (Item *)malloc(n * sizeof(Item));

    // Input values and weights for each item
    for (int i = 0; i < n; i++) {
        printf("Enter value and weight for item %d: ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    // Input capacity of the knapsack
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &W);

    // Calculate maximum value
    int maxValue = knapsack(W, items, n);
    printf("Maximum value in Knapsack = %d\n", maxValue);

    // Free allocated memory
    free(items);

    return 0;
}


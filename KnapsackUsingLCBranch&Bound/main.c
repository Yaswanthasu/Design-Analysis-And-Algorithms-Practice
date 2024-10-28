#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
struct Item {
    int value, weight;
};

// Structure to represent a node in the decision tree
struct Node {
    int level, profit, weight;
    float bound;
};

// Function to calculate the bound (upper limit of profit) for a node
float calculateBound(struct Node u, int n, int maxWeight, struct Item items[]) {
    if (u.weight >= maxWeight) {
        return 0;
    }

    int profitBound = u.profit;
    int totalWeight = u.weight;
    int i = u.level + 1;

    // Add items until the knapsack is full
    while (i < n && totalWeight + items[i].weight <= maxWeight) {
        totalWeight += items[i].weight;
        profitBound += items[i].value;
        i++;
    }

    // Add fractional part of the next item, if possible
    if (i < n) {
        profitBound += (maxWeight - totalWeight) * items[i].value / items[i].weight;
    }

    return profitBound;
}

// Function to compare items based on value-to-weight ratio
int compareItems(const void* a, const void* b) {
    double ratio1 = ((struct Item*)a)->value / (double)((struct Item*)a)->weight;
    double ratio2 = ((struct Item*)b)->value / (double)((struct Item*)b)->weight;
    return (ratio1 > ratio2) ? -1 : 1;
}

// Function to solve the Knapsack problem using Branch and Bound
int knapsack(int maxWeight, struct Item items[], int n) {
    qsort(items, n, sizeof(struct Item), compareItems);  // Sort items by value-to-weight ratio

    struct Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    u.bound = calculateBound(u, n, maxWeight, items);

    int maxProfit = 0;
    struct Node queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = u;  // Add initial node

    while (front < rear) {
        u = queue[front++];  // Get the next node

        if (u.level == n - 1) {
            continue;
        }

        // Include the next item
        v.level = u.level + 1;
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;

        if (v.weight <= maxWeight && v.profit > maxProfit) {
            maxProfit = v.profit;
        }

        v.bound = calculateBound(v, n, maxWeight, items);
        if (v.bound > maxProfit) {
            queue[rear++] = v;  // Add the node to the queue
        }

        // Exclude the next item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = calculateBound(v, n, maxWeight, items);
        if (v.bound > maxProfit) {
            queue[rear++] = v;  // Add the node to the queue
        }
    }

    return maxProfit;
}

int main() {
    int n, maxWeight;

    // Get the number of items and knapsack capacity
    printf("Enter the number of items: ");
    scanf("%d", &n);

    printf("Enter the knapsack capacity: ");
    scanf("%d", &maxWeight);

    struct Item items[n];

    // Get values and weights of items
    for (int i = 0; i < n; i++) {
        printf("Enter value and weight for item %d: ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
    }

    // Call the knapsack function and display the result
    int maxProfit = knapsack(maxWeight, items, n);
    printf("Maximum profit: %d\n", maxProfit);

    return 0;
}

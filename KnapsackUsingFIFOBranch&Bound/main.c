#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
typedef struct {
    int value;
    int weight;
} Item;

// Structure to represent a node in the decision tree
typedef struct {
    int level;   // Level in the decision tree
    int profit;  // Current profit
    int weight;  // Current weight
    float bound; // Upper bound of profit in subtree rooted with this node
} Node;

// Function to calculate the bound of a node
float calculateBound(Node u, int n, int W, Item items[]) {
    if (u.weight >= W) {
        return 0;  // If weight exceeds capacity, bound is 0 (invalid node)
    }

    float profit_bound = u.profit;
    int j = u.level + 1;
    int total_weight = u.weight;

    // Take items while the total weight is less than the capacity
    while (j < n && total_weight + items[j].weight <= W) {
        total_weight += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }

    // If there's still capacity, take a fraction of the next item
    if (j < n) {
        profit_bound += (W - total_weight) * ((float)items[j].value / items[j].weight);
    }

    return profit_bound;
}

// Function to sort items by value/weight ratio
int compare(const void* a, const void* b) {
    float r1 = (float)((Item*)a)->value / ((Item*)a)->weight;
    float r2 = (float)((Item*)b)->value / ((Item*)b)->weight;
    return (r1 > r2) ? -1 : (r1 < r2);
}

// FIFO Branch and Bound function to solve the knapsack problem
int knapsack(Item items[], int n, int W) {
    // Sort items by value/weight ratio
    qsort(items, n, sizeof(Item), compare);

    Node u, v;
    u.level = -1; u.profit = 0; u.weight = 0;

    // Initialize queue for BFS (FIFO)
    Node queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = u;

    int max_profit = 0;

    // Process nodes in queue
    while (front < rear) {
        u = queue[front++];

        if (u.level == n - 1) {
            continue;
        }

        v.level = u.level + 1;

        // Taking the current item
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;

        // If the current item doesn't exceed capacity
        if (v.weight <= W && v.profit > max_profit) {
            max_profit = v.profit;
        }

        v.bound = calculateBound(v, n, W, items);
        if (v.bound > max_profit) {
            queue[rear++] = v;
        }

        // Not taking the current item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = calculateBound(v, n, W, items);

        if (v.bound > max_profit) {
            queue[rear++] = v;
        }
    }

    return max_profit;
}

int main() {
    int n, W;

    // Input number of items and knapsack capacity
    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    Item items[n];

    // Input values and weights of items
    for (int i = 0; i < n; i++) {
        printf("Enter value and weight for item %d: ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
    }

    // Solve the knapsack problem
    int max_profit = knapsack(items, n, W);
    printf("Maximum profit is: %d\n", max_profit);

    return 0;
}

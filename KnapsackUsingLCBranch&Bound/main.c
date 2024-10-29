#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
struct Item {
    int weight;
    int value;
};

// Structure to represent a node in the decision tree
struct Node {
    int level;     // Current level in the tree (current item)
    int profit;    // Total profit so far
    int weight;    // Total weight so far
    float bound;   // Upper bound of profit for this node
};

// Function to calculate the upper bound (best possible profit) for a node
float calculateBound(struct Node u, int n, int capacity, struct Item items[]) {
    if (u.weight >= capacity) {
        return 0;  // If weight exceeds the capacity, bound is 0
    }

    float profit_bound = u.profit;
    int j = u.level + 1;
    int total_weight = u.weight;

    // Add items to the knapsack as long as there's space
    while (j < n && total_weight + items[j].weight <= capacity) {
        total_weight += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }

    // If not enough space for the next item, take the fractional part
    if (j < n) {
        profit_bound += (capacity - total_weight) * (float)items[j].value / items[j].weight;
    }

    return profit_bound;
}

// Comparator function for sorting items by value/weight ratio (greedy)
int compareItems(const void* a, const void* b) {
    struct Item* item1 = (struct Item*)a;
    struct Item* item2 = (struct Item*)b;
    double r1 = (double)item1->value / item1->weight;
    double r2 = (double)item2->value / item2->weight;
    if (r1 > r2) return -1;
    else if (r1 < r2) return 1;
    else return 0;
}

// Function to solve the 0-1 Knapsack using Least Cost Branch and Bound
int knapsack(int capacity, struct Item items[], int n) {
    // Sort items by value/weight ratio in decreasing order
    qsort(items, n, sizeof(struct Item), compareItems);

    // Create an empty queue for the Branch and Bound algorithm
    struct Node queue[1000];
    int front = 0, rear = 0;

    // Add a dummy node as the root of the tree
    struct Node u, v;
    v.level = -1;
    v.profit = 0;
    v.weight = 0;
    v.bound = calculateBound(v, n, capacity, items);
    queue[rear++] = v;

    int max_profit = 0;

    // Branch and Bound loop
    while (front < rear) {
        // Dequeue the front node
        v = queue[front++];

        // If the node's bound is better than the current best, explore it
        if (v.bound > max_profit) {
            // Explore the next level (including the current item)
            u.level = v.level + 1;
            u.weight = v.weight + items[u.level].weight;
            u.profit = v.profit + items[u.level].value;

            // If this is a promising solution, update max_profit
            if (u.weight <= capacity && u.profit > max_profit) {
                max_profit = u.profit;
            }

            // Calculate the upper bound for this node
            u.bound = calculateBound(u, n, capacity, items);

            // If the node is promising, add it to the queue
            if (u.bound > max_profit) {
                queue[rear++] = u;
            }

            // Now explore the next level (excluding the current item)
            u.weight = v.weight;
            u.profit = v.profit;
            u.bound = calculateBound(u, n, capacity, items);

            // If the node is promising, add it to the queue
            if (u.bound > max_profit) {
                queue[rear++] = u;
            }
        }
    }

    return max_profit;
}

int main() {
    int n, capacity;

    // Input: number of items
    printf("Enter the number of items: ");
    scanf("%d", &n);

    // Input: capacity of the knapsack
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    // Declare an array of items
    struct Item items[n];

    // Input: weights and values of each item
    for (int i = 0; i < n; i++) {
        printf("Enter value and weight  of item %d: ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
    }

    // Call the knapsack function
    int maxProfit = knapsack(capacity, items, n);

    // Output: maximum profit
    printf("Maximum Profit: %d\n", maxProfit);

    return 0;
}

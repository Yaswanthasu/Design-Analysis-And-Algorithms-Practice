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

// Priority queue structure for nodes, using an array-based heap
struct PriorityQueue {
    struct Node *nodes;
    int size, capacity;
};

// Helper functions for priority queue
struct PriorityQueue* createPriorityQueue(int capacity) {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->nodes = (struct Node*)malloc(capacity * sizeof(struct Node));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swap(struct Node* a, struct Node* b) {
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}

void insert(struct PriorityQueue* pq, struct Node node) {
    int i = pq->size++;
    pq->nodes[i] = node;
    while (i != 0 && pq->nodes[(i - 1) / 2].bound < pq->nodes[i].bound) {
        swap(&pq->nodes[i], &pq->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

struct Node extractMax(struct PriorityQueue* pq) {
    struct Node root = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    int i = 0, largest = 0;
    while ((2 * i + 1) < pq->size) {
        int left = 2 * i + 1, right = 2 * i + 2;
        largest = (right < pq->size && pq->nodes[right].bound > pq->nodes[left].bound) ? right : left;
        if (pq->nodes[i].bound >= pq->nodes[largest].bound) break;
        swap(&pq->nodes[i], &pq->nodes[largest]);
        i = largest;
    }
    return root;
}

// Function to solve the Knapsack problem using LC Branch and Bound
int knapsack(int maxWeight, struct Item items[], int n) {
    qsort(items, n, sizeof(struct Item), compareItems);  // Sort items by value-to-weight ratio

    struct PriorityQueue* pq = createPriorityQueue(1000);

    struct Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    u.bound = calculateBound(u, n, maxWeight, items);

    int maxProfit = 0;
    int globalUpperBound = u.bound;  // Initialize global upper bound

    insert(pq, u);  // Add initial node

    while (pq->size > 0) {
        u = extractMax(pq);  // Get node with the highest bound

        if (u.bound <= maxProfit || u.level == n - 1) {
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
            globalUpperBound = (v.bound > globalUpperBound) ? v.bound : globalUpperBound;  // Update global upper bound
            insert(pq, v);
        }

        // Exclude the next item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = calculateBound(v, n, maxWeight, items);
        if (v.bound > maxProfit) {
            globalUpperBound = (v.bound > globalUpperBound) ? v.bound : globalUpperBound;  // Update global upper bound
            insert(pq, v);
        }
    }

    free(pq->nodes);
    free(pq);

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

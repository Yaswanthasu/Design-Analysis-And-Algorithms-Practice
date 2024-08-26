#include <stdio.h>

#define V 4
#define INF 99999

// Function to implement Floyd-Warshall algorithm
void floyd_warshall(int graph[V][V]) {
    int dist[V][V], i, j, k;

    // Initialize the distance matrix with the input graph
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Update the distance matrix with shortest distances
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the final shortest distance matrix
    print_solution(dist);
}

void print_solution(int dist[V][V]) {
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to take graph input from user
void input_graph(int graph[V][V]) {
    printf("Enter the adjacency matrix (use %d for infinity):\n", INF);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
}

// Example usage:
int main() {
    int graph[V][V];

    // Take graph input from user
    input_graph(graph);

    // Apply Floyd-Warshall algorithm
    floyd_warshall(graph);

    return 0;
}

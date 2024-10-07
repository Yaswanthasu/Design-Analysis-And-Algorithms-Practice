#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool Ismatch(int currvertex, int color[], int N, int adj[N][N], int c) {
    for (int k = 0; k < N; k++) {
        if (adj[currvertex][k] == 1 && color[k] == c) {
            return true;
        }
    }
    return false;
}

void GraphColoring(int currvertex, int m, int N, int adj[N][N], int color[]) {
    if (currvertex == N) {
        for (int i = 0; i < N; i++) {
            printf("Vertex %d -> Color %d\n", i, color[i]);
        }
        printf("\n");

        return;
    }

    for (int j = 1; j <= m; j++) {
        if (!Ismatch(currvertex, color, N, adj, j)) {
            color[currvertex] = j;

            GraphColoring(currvertex + 1, m, N, adj, color);

            color[currvertex] = 0;
        }
    }
}

int main() {
    int N, m;

    printf("Enter the number of vertices: ");
    scanf("%d", &N);

    printf("Enter the number of colors: ");
    scanf("%d", &m);

    int adj[N][N];

    printf("Enter the adjacency matrix (%d x %d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    int color[N];
    for (int i = 0; i < N; i++) {
        color[i] = 0;
    }

    printf("All valid color arrangements:\n");
    GraphColoring(0, m, N, adj, color);

    return 0;
}

// C program to solve the N-Queens problem using backtracking

#include <stdio.h>
#include <stdbool.h>

void print_solution(int board[][20], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

bool is_safe(int board[][20], int row, int col, int N) {
    int i, j;

    // Check this row on the left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on the left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on the left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool solve_n_queens_util(int board[][20], int col, int N) {
    // If all queens are placed, return true
    if (col >= N)
        return true;

    // Consider this column and try placing the queen in all rows
    for (int i = 0; i < N; i++) {
        if (is_safe(board, i, col, N)) {
            // Place this queen
            board[i][col] = 1;

            // Recur to place the rest of the queens
            if (solve_n_queens_util(board, col + 1, N))
                return true;

            // If placing queen doesn't lead to a solution, backtrack
            board[i][col] = 0;
        }
    }

    return false;
}

void solve_n_queens(int N) {
    int board[20][20] = {0};  // Create a board with a maximum size of 20x20

    if (!solve_n_queens_util(board, 0, N))
        printf("No solution exists\n");
    else
        print_solution(board, N);
}

int main() {
    int N;
    printf("Enter the value of N: ");
    scanf("%d", &N);  // Taking input from the user
    solve_n_queens(N);
    return 0;
}


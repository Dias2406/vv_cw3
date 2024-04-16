#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Utility functions to check if the current position is safe for placing a queen
int isSafe(char **board, int row, int col, int n) {
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i] == 'Q')
            return 0;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'Q')
            return 0;

    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < n; i++, j--)
        if (board[i][j] == 'Q')
            return 0;

    return 1;
}

// A utility function to solve N Queen problem
void solveNQUtil(char **board, int col, int n, char ****solutions, int *returnSize, int *returnColumnSizes) {
    int i;
    if (col >= n) {
        // When n queens are placed successfully
        char **solution = malloc(n * sizeof(char *));
        for (i = 0; i < n; i++) {
            solution[i] = strdup(board[i]); // Copy solution
        }
        (*solutions)[*returnSize] = solution;
        returnColumnSizes[*returnSize] = n;
        (*returnSize)++;
        return;
    }

    // Consider this column and try placing this queen in all rows one by one
    for (i = 0; i < n; i++) {
        if ( isSafe(board, i, col, n) ) {
            board[i][col] = 'Q';

            // Recur to place rest of the queens
            solveNQUtil(board, col + 1, n, solutions, returnSize, returnColumnSizes);

            // If placing queen in board[i][col] doesn't lead to a solution then
            // remove queen from board[i][col]
            board[i][col] = '.';
        }
    }
}

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    char ***solutions = malloc(500 * sizeof(char **)); // Allocate memory for solutions
    *returnColumnSizes = malloc(500 * sizeof(int)); // Allocate memory for column sizes
    *returnSize = 0;
    char **board = malloc(n * sizeof(char *));
    int i, j;
    for (i = 0; i < n; i++) {
        board[i] = malloc((n + 1) * sizeof(char));
        for (j = 0; j < n; j++)
            board[i][j] = '.';
        board[i][n] = '\0';
    }

    // Solve the N Queens problem with backtracking
    solveNQUtil(board, 0, n, &solutions, returnSize, *returnColumnSizes);
    
    // Clean up temporary board
    for (i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
    
    return solutions;
}

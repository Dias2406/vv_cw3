#include <stdbool.h>

#define N_MAX 10

bool isSafe(char board[][N_MAX], int row, int col, int n) {
    // Check if there's a queen in the same column
    for (int i = 0; i < row; ++i)
        if (board[i][col] == 'Q')
            return false;
    
    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
        if (board[i][j] == 'Q')
            return false;
    
    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; --i, ++j)
        if (board[i][j] == 'Q')
            return false;
    
    return true;
}

void solveNQueens(char board[][N_MAX], int row, int n, int* count) {
    if (row == n) {
        (*count)++; // Found a solution
        return;
    }
    
    for (int col = 0; col < n; ++col) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 'Q'; // Place the queen
            
            // Recur for the next row
            solveNQueens(board, row + 1, n, count);
            
            // Backtrack
            board[row][col] = '.';
        }
    }
}

int totalNQueens(int n) {
    int count = 0;
    char board[N_MAX][N_MAX];
    
    // Initialize board with empty cells
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            board[i][j] = '.';
    
    // Start placing queens from the first row
    solveNQueens(board, 0, n, &count);
    
    return count;
}

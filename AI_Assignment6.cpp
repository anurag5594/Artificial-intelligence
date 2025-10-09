#include <iostream>
#include <vector>
using namespace std;

const int N = 8;   // Size of chessboard (8x8)

// Function to print the board
void printBoard(const vector<int> &board) {
    cout << "\nSolution:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                cout << " Q ";
            else
                cout << " . ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Check if the queen can be placed at (row, col)
bool isSafe(const vector<int> &board, int row, int col) {
    for (int i = 0; i < row; i++) {
        // Check same column
        if (board[i] == col)
            return false;
        // Check diagonals
        if (abs(board[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

// Backtracking function to solve N-Queens
void solveNQueens(vector<int> &board, int row, int &solutionCount) {
    if (row == N) {
        // All queens placed
        solutionCount++;
        printBoard(board);
        return;
    }

    // Try placing a queen in each column of the current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;                   // Place queen
            solveNQueens(board, row + 1, solutionCount);  // Recur
            board[row] = -1;                    // Backtrack
        }
    }
}

int main() {
    vector<int> board(N, -1);  // board[i] = column of queen in row i
    int solutionCount = 0;

    cout << "Solving 8-Queens Problem using Backtracking...\n";
    solveNQueens(board, 0, solutionCount);

    cout << "Total solutions found: " << solutionCount << "\n";
    return 0;
}

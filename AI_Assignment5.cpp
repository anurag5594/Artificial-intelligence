#include <iostream>
#include <limits>
using namespace std;

const char PLAYER = 'X';      // Human
const char AI = 'O';          // Computer
const char EMPTY = '_';

char board[3][3] = {
    { EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY }
};

// Function to print the board
void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Check if there are any moves left
bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return true;
    return false;
}

// Evaluation function
int evaluate() {
    // Check rows for win
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2]) {
            if (board[row][0] == AI)
                return +10;
            else if (board[row][0] == PLAYER)
                return -10;
        }
    }

    // Check columns for win
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col]) {
            if (board[0][col] == AI)
                return +10;
            else if (board[0][col] == PLAYER)
                return -10;
        }
    }

    // Check diagonals for win
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == AI)
            return +10;
        else if (board[0][0] == PLAYER)
            return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == AI)
            return +10;
        else if (board[0][2] == PLAYER)
            return -10;
    }

    // No winner
    return 0;
}

// Minimax algorithm
int minimax(int depth, bool isMax) {
    int score = evaluate();

    // If AI has won
    if (score == 10)
        return score - depth;  // Prefer quicker wins

    // If Player has won
    if (score == -10)
        return score + depth;  // Prefer delayed loss

    // If no moves left => draw
    if (!isMovesLeft())
        return 0;

    // Maximizing player (AI)
    if (isMax) {
        int best = numeric_limits<int>::min();

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check empty cell
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;          // Make move
                    best = max(best, minimax(depth + 1, false));
                    board[i][j] = EMPTY;       // Undo move
                }
            }
        }
        return best;
    }
    // Minimizing player (Human)
    else {
        int best = numeric_limits<int>::max();

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check empty cell
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;      // Make move
                    best = min(best, minimax(depth + 1, true));
                    board[i][j] = EMPTY;       // Undo move
                }
            }
        }
        return best;
    }
}

// Find best move for AI
pair<int,int> findBestMove() {
    int bestVal = numeric_limits<int>::min();
    pair<int,int> bestMove = {-1, -1};

    // Traverse all cells
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check empty cell
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;    // Make move
                int moveVal = minimax(0, false);
                board[i][j] = EMPTY; // Undo move

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

int main() {
    cout << "Tic-Tac-Toe Game (You = X, AI = O)\n";

    int moveCount = 0;
    while (true) {
        printBoard();
        if (evaluate() == 10) {
            cout << "AI Wins!\n";
            break;
        } else if (evaluate() == -10) {
            cout << "You Win!\n";
            break;
        } else if (!isMovesLeft()) {
            cout << "It's a Draw!\n";
            break;
        }

        if (moveCount % 2 == 0) {
            // Human's turn
            int r, c;
            cout << "Enter your move (row[0-2] col[0-2]): ";
            cin >> r >> c;
            if (r >= 0 && r < 3 && c >= 0 && c < 3 && board[r][c] == EMPTY)
                board[r][c] = PLAYER;
            else {
                cout << "Invalid move! Try again.\n";
                continue;
            }
        } else {
            // AI's turn
            cout << "AI is making a move...\n";
            pair<int,int> bestMove = findBestMove();
            board[bestMove.first][bestMove.second] = AI;
        }
        moveCount++;
    }

    printBoard();
    return 0;
}

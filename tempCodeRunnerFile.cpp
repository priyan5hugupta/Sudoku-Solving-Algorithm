#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <chrono>

using namespace std;

// Define the size of the Sudoku grid (usually 9x9)
const int N = 9;

// Define a structure to represent a Sudoku board state
struct State {
    int board[N][N];
    int row, col; // Coordinates of the next empty cell to be filled
};

// Function to check if a number can be placed in a cell
bool isSafe(State &state, int num) {
    int row = state.row;
    int col = state.col;

    // Check the row and column for the same number
    for (int i = 0; i < N; i++) {
        if (state.board[row][i] == num || state.board[i][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid for the same number
    int subgridRow = row - row % 3;
    int subgridCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state.board[i + subgridRow][j + subgridCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve Sudoku using BFS with backtracking
bool solveSudokuBFS(vector<vector<int>> &initialBoard) {
    queue<State> q;
    State initialState;
    initialState.row = 0;
    initialState.col = 0;

    // Copy the initial board state
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            initialState.board[i][j] = initialBoard[i][j];
        }
    }

    q.push(initialState);

    while (!q.empty()) {
        State currentState = q.front();
        q.pop();

        // If there are no empty cells left, the Sudoku is solved
        if (currentState.row == N) {
            vector<vector<int>> sBoard(N, vector<int>(N, 0));
            // Print the solved Sudoku board
            cout << endl;
            cout << endl;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    sBoard[i][j] = currentState.board[i][j];
                    cout << currentState.board[i][j] << " ";
                }
                cout << endl;
            }

            return true;
        }

        // Find the next empty cell
        while (currentState.row < N && currentState.board[currentState.row][currentState.col] != 0) {
            currentState.col++;
            if (currentState.col == N) {
                currentState.col = 0;
                currentState.row++;
            }
        }

        // Try filling the cell with numbers 1 to 9
        for (int num = 1; num <= 9; num++) {
            if (isSafe(currentState, num)) {
                State nextState = currentState;
                nextState.board[currentState.row][currentState.col] = num;
                nextState.col++; // Move to the next cell
                if (nextState.col == N) {
                    nextState.col = 0;
                    nextState.row++;
                }
                q.push(nextState);
            }
        }
    }

    return false; // No solution found
}

int main() 
{
    vector<vector<int>> initialBoard(N, vector<int>(N, 0)); // Initialize an empty Sudoku board

    // Read the initial Sudoku board state from input (0 for empty cells)
    cout << "Enter the initial Sudoku board (use 0 for empty cells):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> initialBoard[i][j];
        }
    }
    // Record the start time
    auto start_time = std::chrono::high_resolution_clock::now();
    if (solveSudokuBFS(initialBoard)) {
        cout << "Sudoku solved!" << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    // Record the end time
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Print the elapsed time in microseconds
    std::cout << "Time taken by code: " << duration.count() << " microseconds" << std::endl;

    return 0;
}


#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>

using namespace std;

// Define the size of the Sudoku grid (usually 9x9)
const int N = 9;

// Function to check if a number is valid in a given row
bool isValidInRow(const vector<vector<int>>& board, int row) {
    unordered_set<int> seen; // Create an unordered set to store seen numbers in the row
    for (int col = 0; col < 9; col++) { // Iterate through each column in the row
        int num = board[row][col]; // Get the number in the current cell
        if (num == 0 || seen.count(num)) { // Check if the number is 0 (empty cell) or if it has been seen before
            return false; // If the number is not valid, return false
        }
        seen.insert(num); // Add the number to the set of seen numbers
    }
    return true; // If all numbers in the row are valid, return true
}

// Function to check if a number is valid in a given column
bool isValidInCol(const vector<vector<int>>& board, int col) {
    unordered_set<int> seen; // Create an unordered set to store seen numbers in the column
    for (int row = 0; row < 9; row++) { // Iterate through each row in the column
        int num = board[row][col]; // Get the number in the current cell
        if (num == 0 || seen.count(num)) { // Check if the number is 0 (empty cell) or if it has been seen before
            return false; // If the number is not valid, return false
        }
        seen.insert(num); // Add the number to the set of seen numbers
    }
    return true; // If all numbers in the column are valid, return true
}

// Function to check if a number is valid in a 3x3 subgrid (box)
bool isValidInBox(const vector<vector<int>>& board, int startRow, int startCol) {
    unordered_set<int> seen; // Create an unordered set to store seen numbers in the subgrid
    for (int row = 0; row < 3; row++) { // Iterate through each row in the subgrid
        for (int col = 0; col < 3; col++) { // Iterate through each column in the subgrid
            int num = board[startRow + row][startCol + col]; // Get the number in the current cell
            if (num == 0 || seen.count(num)) { // Check if the number is 0 (empty cell) or if it has been seen before
                return false; // If the number is not valid, return false
            }
            seen.insert(num); // Add the number to the set of seen numbers
        }
    }
    return true; // If all numbers in the subgrid are valid, return true
}

// Function to validate a complete Sudoku board
bool isValidSudoku(const vector<vector<int>>& board) {
    // Check each row
    for (int row = 0; row < 9; row++) { // Iterate through each row in the board
        if (!isValidInRow(board, row)) { // Check if the row is not valid using isValidInRow
            return false; // If any row is not valid, return false
        }
    }

    // Check each column
    for (int col = 0; col < 9; col++) { // Iterate through each column in the board
        if (!isValidInCol(board, col)) { // Check if the column is not valid using isValidInCol
            return false; // If any column is not valid, return false
        }
    }

    // Check each 3x3 subgrid (box)
    for (int startRow = 0; startRow < 9; startRow += 3) { // Iterate through subgrid rows
        for (int startCol = 0; startCol < 9; startCol += 3) { // Iterate through subgrid columns
            if (!isValidInBox(board, startRow, startCol)) { // Check if the subgrid is not valid using isValidInBox
                return false; // If any subgrid is not valid, return false
            }
        }
    }

    return true; // If all rows, columns, and subgrids are valid, return true (a valid Sudoku).
}

// Function to print the Sudoku board
void printBoard(const vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " "; // Print each cell in the Sudoku board
        }
        cout << endl;
    }
    if (isValidSudoku(board)) 
    {
        cout << "Valid Sudoku Solution." << endl;
    } else 
    {
        cout << "Invalid Sudoku Solution." << endl;
    }
}

// Function to check if a number can be placed in a cell
bool isSafe(vector<vector<int>> &board, int row, int col, int num) {
    // Check the row and column for the same number
    for (int i = 0; i < N; i++) { // Loop through each row and column
        if (board[row][i] == num || board[i][col] == num) { // Check if the number already exists in the row or column
            return false; // If the number is not safe to place, return false
        }
    }

    // Check the 3x3 subgrid for the same number
    int subgridRow = row - row % 3; // Calculate the starting row of the 3x3 subgrid
    int subgridCol = col - col % 3; // Calculate the starting column of the 3x3 subgrid
    for (int i = 0; i < 3; i++) { // Loop through each row in the subgrid
        for (int j = 0; j < 3; j++) { // Loop through each column in the subgrid
            if (board[i + subgridRow][j + subgridCol] == num) { // Check if the number exists in the subgrid
                return false; // If the number is not safe to place, return false
            }
        }
    }

    return true; // If the number can be safely placed, return true
}

// Function to solve Sudoku using backtracking with DLS traversal
bool solveSudokuDLS(vector<vector<int>> &board, int depth, int maxDepth) {
    if (depth > maxDepth) { // Check if the depth limit has been reached
        return false; // If the depth limit is exceeded, return false (backtrack)
    }

    for (int row = 0; row < N; row++) { // Loop through each row in the Sudoku board
        for (int col = 0; col < N; col++) { // Loop through each column in the Sudoku board
            if (board[row][col] == 0) { // Check if the cell is empty
                for (int num = 1; num <= N; num++) { // Try numbers from 1 to N
                    if (isSafe(board, row, col, num)) { // Check if it's safe to place the number
                        board[row][col] = num; // Place the number
                        if (solveSudokuDLS(board, depth + 1, maxDepth)) { // Recursively solve the Sudoku
                            return true; // If a solution is found, return true
                        }
                        board[row][col] = 0; // Backtrack by setting the cell to 0
                    }
                }
                return false; // If no valid number can be placed, return false (backtrack)
            }
        }
    }

    return true; // If all cells are filled and the Sudoku is solved, return true
}

int main() {
    vector<vector<int>> board(N, vector<int>(N, 0)); // Initialize an empty Sudoku board

    // Read the initial Sudoku board state from input (0 for empty cells)
    cout << "Enter the initial Sudoku board (use 0 for empty cells):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }
    // Record the start time
    auto start_time = std::chrono::high_resolution_clock::now();
    int maxDepth = N * N; // Set a depth limit equal to the number of cells
    if (solveSudokuDLS(board, 0, maxDepth)) { // Solve Sudoku using Depth-Limited Search (DLS)
        cout << "Sudoku solved!" << endl;
        printBoard(board); // Print the solved Sudoku board
    } else {
        cout << "No solution exists." << endl; // If no solution exists, print a message
    }

    // Record the end time
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Print the elapsed time in microseconds
    std::cout << "Time taken by code: " << duration.count() << " microseconds" << std::endl;

    return 0;
}

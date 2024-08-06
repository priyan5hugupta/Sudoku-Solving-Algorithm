#include <iostream>
#include <vector>

using namespace std;

const int N = 9; // Size of the Sudoku grid
const int SUBGRID_SIZE = 3; // Size of each 3x3 subgrid

// Define a structure for the Dancing Links nodes
struct Node {
    Node* left;
    Node* right;
    Node* up;
    Node* down;
    Node* colHeader;
    int row;
    int col;
};

// Function to create a new Dancing Links node
Node* createNode(int row, int col) {
    Node* newNode = new Node;
    newNode->left = newNode->right = newNode->up = newNode->down = newNode;
    newNode->colHeader = nullptr;
    newNode->row = row;
    newNode->col = col;
    return newNode;
}

// Function to cover a column in the exact cover matrix
void cover(Node* colHeader) {
    colHeader->right->left = colHeader->left;
    colHeader->left->right = colHeader->right;

    for (Node* rowNode = colHeader->down; rowNode != colHeader; rowNode = rowNode->down) {
        for (Node* rightNode = rowNode->right; rightNode != rowNode; rightNode = rightNode->right) {
            rightNode->up->down = rightNode->down;
            rightNode->down->up = rightNode->up;
        }
    }
}

// Function to uncover a column in the exact cover matrix
void uncover(Node* colHeader) {
    for (Node* rowNode = colHeader->up; rowNode != colHeader; rowNode = rowNode->up) {
        for (Node* leftNode = rowNode->left; leftNode != rowNode; leftNode = leftNode->left) {
            leftNode->up->down = leftNode;
            leftNode->down->up = leftNode;
        }
    }

    colHeader->right->left = colHeader;
    colHeader->left->right = colHeader;
}

// Function to solve the exact cover problem using Dancing Links
bool solveExactCover(Node* header) {
    if (header->right == header) {
        return true; // Solution found
    }

    Node* colHeader = header->right;
    cover(colHeader);

    for (Node* rowNode = colHeader->down; rowNode != colHeader; rowNode = rowNode->down) {
        for (Node* rightNode = rowNode->right; rightNode != rowNode; rightNode = rightNode->right) {
            cover(rightNode->colHeader);
        }

        if (solveExactCover(header)) {
            return true;
        }

        for (Node* leftNode = rowNode->left; leftNode != rowNode; leftNode = leftNode->left) {
            uncover(leftNode->colHeader);
        }
    }

    uncover(colHeader);
    return false; // No solution found
}


// Function to solve Sudoku using Dancing Links
bool solveSudokuDLX(vector<vector<int>>& puzzle) {
    // Create the exact cover matrix
    vector<Node*> nodes;
    Node* header = createNode(-1, -1);
    nodes.push_back(header);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] == 0) {
                for (int num = 1; num <= N; num++) {
                    Node* rowNode = createNode(i, j);
                    Node* colNode1 = createNode(i, num - 1);
                    Node* colNode2 = createNode(j + N, num - 1);
                    Node* colNode3 = createNode((i / SUBGRID_SIZE) * SUBGRID_SIZE + (j / SUBGRID_SIZE) + 2 * N, num - 1);

                    rowNode->left = colNode3;
                    rowNode->right = colNode1;
                    colNode1->left = rowNode;
                    colNode1->right = colNode2;
                    colNode2->left = colNode1;
                    colNode2->right = colNode3;
                    colNode3->left = colNode2;
                    colNode3->right = rowNode;

                    rowNode->up = nodes[num - 1]->up;
                    rowNode->down = nodes[num - 1];
                    nodes[num - 1]->up->down = rowNode;
                    nodes[num - 1]->up = rowNode;
                    rowNode->colHeader = colNode1;
                }
            } else {
                Node* rowNode = createNode(i, j);
                Node* colNode1 = createNode(i, puzzle[i][j] - 1);
                Node* colNode2 = createNode(j + N, puzzle[i][j] - 1);
                Node* colNode3 = createNode((i / SUBGRID_SIZE) * SUBGRID_SIZE + (j / SUBGRID_SIZE) + 2 * N, puzzle[i][j] - 1);

                rowNode->left = colNode3;
                rowNode->right = colNode1;
                colNode1->left = rowNode;
                colNode1->right = colNode2;
                colNode2->left = colNode1;
                colNode2->right = colNode3;
                colNode3->left = colNode2;
                colNode3->right = rowNode;

                rowNode->up = nodes[puzzle[i][j] - 1]->up;
                rowNode->down = nodes[puzzle[i][j] - 1];
                nodes[puzzle[i][j] - 1]->up->down = rowNode;
                nodes[puzzle[i][j] - 1]->up = rowNode;
                rowNode->colHeader = colNode1;
            }
        }
    }

    // Initialize the root node
    header->right = nodes[0];
    header->left = nodes[N - 1];
    nodes[0]->left = header;
    nodes[N - 1]->right = header;

    // Solve Sudoku using Dancing Links (exact cover problem)
    return solveExactCover(header);
}


// Function to print the Sudoku board
void printBoard(vector<vector<int>>& puzzle) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to read Sudoku input from the user
void readSudokuInput(vector<vector<int>>& puzzle) {
    cout << "Enter Sudoku puzzle (use 0 for empty cells):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> puzzle[i][j];
        }
    }
}

int main() {
    vector<vector<int>> puzzle(N, vector<int>(N, 0));

    readSudokuInput(puzzle);

    if (solveSudokuDLX(puzzle)) {
        cout << "Solved Sudoku:" << endl;
        printBoard(puzzle);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}

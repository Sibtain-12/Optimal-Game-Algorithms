#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class SudokuSolver {
private:
    vector<vector<int>> board;
    static const int SIZE = 9;
    static const int BOX_SIZE = 3;
    
    // Check if placing num at (row, col) is valid
    bool isValid(int row, int col, int num) {
        // Check row
        for (int j = 0; j < SIZE; j++) {
            if (board[row][j] == num) return false;
        }
        
        // Check column
        for (int i = 0; i < SIZE; i++) {
            if (board[i][col] == num) return false;
        }
        
        // Check 3x3 box
        int boxRow = (row / BOX_SIZE) * BOX_SIZE;
        int boxCol = (col / BOX_SIZE) * BOX_SIZE;
        
        for (int i = boxRow; i < boxRow + BOX_SIZE; i++) {
            for (int j = boxCol; j < boxCol + BOX_SIZE; j++) {
                if (board[i][j] == num) return false;
            }
        }
        
        return true;
    }
    
    // Count possible values for a cell (for MRV heuristic)
    int countPossibilities(int row, int col) {
        if (board[row][col] != 0) return SIZE + 1;
        
        int count = 0;
        for (int num = 1; num <= SIZE; num++) {
            if (isValid(row, col, num)) count++;
        }
        return count;
    }
    
    // Find empty cell with minimum remaining values (MRV heuristic)
    bool findBestEmptyCell(int& row, int& col) {
        int minPossibilities = SIZE + 1;
        bool found = false;
        
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0) {
                    int possibilities = countPossibilities(i, j);
                    
                    // Early termination if only one option
                    if (possibilities == 0) return false;
                    
                    if (possibilities < minPossibilities) {
                        minPossibilities = possibilities;
                        row = i;
                        col = j;
                        found = true;
                        
                        if (possibilities == 1) return true;
                    }
                }
            }
        }
        return found;
    }
    
    // Backtracking solver with MRV optimization
    bool solve() {
        int row = -1, col = -1;
        
        // Find best empty cell using MRV heuristic
        if (!findBestEmptyCell(row, col)) {
            return row == -1;  // No empty cells means solved
        }
        
        // Try each number from 1 to 9
        for (int num = 1; num <= SIZE; num++) {
            if (isValid(row, col, num)) {
                board[row][col] = num;
                
                if (solve()) return true;
                
                // Backtrack
                board[row][col] = 0;
            }
        }
        
        return false;
    }

public:
    SudokuSolver() {
        board.resize(SIZE, vector<int>(SIZE, 0));
    }
    
    // Input sudoku from user
    void inputBoard() {
        cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";
        cout << "Enter 9 numbers per row, separated by spaces:\n\n";
        
        for (int i = 0; i < SIZE; i++) {
            cout << "Row " << (i + 1) << ": ";
            for (int j = 0; j < SIZE; j++) {
                cin >> board[i][j];
                
                // Validate input
                if (board[i][j] < 0 || board[i][j] > 9) {
                    cout << "Invalid input! Use numbers 0-9 only.\n";
                    j--;  // Re-enter this value
                }
            }
        }
    }
    
    // Alternative: Quick input (single line per row)
    void inputBoardCompact() {
        cout << "Enter the Sudoku puzzle (9 rows of 9 digits, use 0 for empty):\n";
        cout << "Example: 530070000\n\n";
        
        string line;
        for (int i = 0; i < SIZE; i++) {
            cout << "Row " << (i + 1) << ": ";
            cin >> line;
            
            if (line.length() != SIZE) {
                cout << "Invalid input! Enter exactly 9 digits.\n";
                i--;
                continue;
            }
            
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = line[j] - '0';
                
                if (board[i][j] < 0 || board[i][j] > 9) {
                    cout << "Invalid digit! Use 0-9 only.\n";
                    i--;
                    break;
                }
            }
        }
    }
    
    // Print the board in a formatted way
    void printBoard() const {
        cout << "\n";
        for (int i = 0; i < SIZE; i++) {
            if (i % BOX_SIZE == 0 && i != 0) {
                cout << "------+-------+------\n";
            }
            
            for (int j = 0; j < SIZE; j++) {
                if (j % BOX_SIZE == 0 && j != 0) {
                    cout << "| ";
                }
                
                if (board[i][j] == 0) {
                    cout << ". ";
                } else {
                    cout << board[i][j] << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    // Public solve method
    bool solvePuzzle() {
        return solve();
    }
    
    // Validate if initial board is correct
    bool validateBoard() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] != 0) {
                    int temp = board[i][j];
                    board[i][j] = 0;
                    
                    if (!isValid(i, j, temp)) {
                        board[i][j] = temp;
                        return false;
                    }
                    
                    board[i][j] = temp;
                }
            }
        }
        return true;
    }
};

int main() {
    SudokuSolver solver;
    
    cout << "=== Optimized Sudoku Solver ===\n\n";
    cout << "Choose input method:\n";
    cout << "1. Space-separated input\n";
    cout << "2. Compact input (9 digits per line)\n";
    cout << "Enter choice (1 or 2): ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        solver.inputBoard();
    } else {
        solver.inputBoardCompact();
    }
    
    cout << "\nOriginal Puzzle:";
    solver.printBoard();
    
    // Validate initial board
    if (!solver.validateBoard()) {
        cout << "Error: Invalid initial puzzle! Contains conflicts.\n";
        return 1;
    }
    
    cout << "Solving...\n";
    
    if (solver.solvePuzzle()) {
        cout << "✓ Solution found!\n";
        cout << "\nSolved Puzzle:";
        solver.printBoard();
    } else {
        cout << "✗ No solution exists for this puzzle.\n";
    }
    
    return 0;
}

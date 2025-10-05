# Optimal Game Algorithms

A collection of classic games and puzzles implemented in C/C++ with optimal algorithmic strategies using game theory, backtracking, etc..

## Overview

This repository contains optimized implementations of six strategy games and puzzles. Each implementation features intelligent AI opponents that use proven algorithms for optimal or near-optimal play.

## Games Included

### 1. **Sim** (`sim.c`)
A two-player graph theory game played on 6 vertices where players take turns coloring edges, trying to avoid forming a monochromatic triangle.

**How to Play:**
- 6 vertices connected by 15 possible edges (complete graph K₆)
- Players alternate coloring edges (Red vs Blue)
- First player to complete a triangle in their color LOSES
- Input format: Two-digit numbers representing edges (e.g., 12 for edge between vertices 1-2)
- Valid edges: 12, 13, 14, 15, 16, 23, 24, 25, 26, 34, 35, 36, 45, 46, 56

### 2. **Connect4** (`connect4.c`)
Classic connection game on a 4×5 board where players drop colored pieces aiming to connect four in a row.

**How to Play:**
- 4 rows × 5 columns board
- Choose Red (R) or Blue (B)
- Enter column number (0-4) to drop your piece
- Win by connecting 4 pieces horizontally, vertically, or diagonally

### 3. **2×2×2 Rubik's Cube Solver** (`rubric.cpp`)
Solves the Pocket Cube using breadth-first search to find optimal move sequences.

**How to Play:**
- Input the scrambled cube configuration (8 corner pieces with 3 colors each)
- Each corner: 3 letters representing colors (G/B/O/R/W/Y)
- Cube must be oriented with Orange face forward
- Solver outputs optimal move sequence

### 4. **Sudoku Solver** (`sudokuSolver.cpp`)
Efficient 9×9 Sudoku solver using backtracking with the Minimum Remaining Values heuristic.

**How to Play:**
- Choose input method (space-separated or compact 9-digit format)
- Enter 9 rows of 9 numbers each
- Use 0 for empty cells
- Solver validates and finds solution

### 5. **Race to N** (`race_to_N.cpp`)
Strategic number game where players add values within a range, racing to reach target N first.

**How to Play:**
- Set target number N
- Define min and max values to add per turn
- Choose game mode (vs Opponent, vs AI first, or AI first)
- Reach exactly N to win

### 6. **Up It Up** (`up_it_up.cpp`)
A dice-rolling puzzle solver where cubes surrounding an empty center space roll into the empty position, changing which face is visible from the top view.
- 3×3 grid with 8 dice/cubes surrounding an empty center space (i.e., 0)
- Each cube is a standard die: 1=top, 2=bottom, 3=right side, 4=left side, 5=front, 6=back
- Default initial state: all cubes show face 2 from top view (bottom face up), center is empty
- Goal state: all cubes show face 1 from top view (top face up) and center empty (i.e., 0)

**How to Play:**
- By default the input configuration is all cubes show face 2 from top view (bottom face up), center is empty
- To enable input (what number each cube shows from top view) : uncomment ```cin>>value;``` in the ```read_game_board()``` function
- Solver automatically finds the optimal move sequence for the empty space


#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include<tuple>
#include<cmath>
#include<queue>
#include<assert.h>
#include <cstdint>
#include <queue>
using namespace std;

struct GameBoard{
    int grid[3][3];
};

enum {
    PLAYER_X=1,
    PLAYER_O=2
};

void display_board(const GameBoard& gameBoard){
    for(int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            cout << gameBoard.grid[row][col] << " ";
        }
        cout << endl;
    }
}

pair<int,int> find_empty_space(const GameBoard& gameBoard){
    int row=0, col=0;
    for(row=0;row<3;row++){
        for(col=0;col<3;col++){
            if(gameBoard.grid[row][col] == 0){
                return make_pair(row, col);
            }
        }
    }
    assert(0);
}

bool is_valid(const GameBoard& gameBoard){
    for(int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            if(gameBoard.grid[row][col] > 1){
                return false;
            }
            if(row * col == 1){
                if(gameBoard.grid[1][1] != 0){
                    return false;
                }
            }
        }
    }
    return true;
}

int board_order(const GameBoard& gameBoard){
    int order=0;
    int index=0;
    for(int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            order += gameBoard.grid[row][col] * pow(7, index);
            index++;
        }
    }
    return order;
}

GameBoard move_up(GameBoard currentBoard, int row, int col){
    GameBoard newBoard = currentBoard;
    int value = currentBoard.grid[row-1][col];
    if(value == 1){ value = 6; }
    else if(value == 2){ value = 5; }
    else if(value == 5){ value = 1; }
    else if(value == 6){ value = 2; }
    newBoard.grid[row][col] = value;
    newBoard.grid[row-1][col] = 0;
    return newBoard;
}

GameBoard move_down(const GameBoard& currentBoard, int row, int col){
    GameBoard newBoard = currentBoard;
    int value = currentBoard.grid[row+1][col];
    if(value == 1){ value = 5; }
    else if(value == 2){ value = 6; }
    else if(value == 5){ value = 2; }
    else if(value == 6){ value = 1; }
    newBoard.grid[row][col] = value;
    newBoard.grid[row+1][col] = 0;
    return newBoard;
}

GameBoard move_left(const GameBoard& currentBoard, int row, int col){
    GameBoard newBoard = currentBoard;
    int value = currentBoard.grid[row][col-1];
    if(value == 1){ value = 4; }
    else if(value == 2){ value = 3; }
    else if(value == 3){ value = 1; }
    else if(value == 4){ value = 2; }
    newBoard.grid[row][col] = value;
    newBoard.grid[row][col-1] = 0;
    return newBoard;
}

GameBoard move_right(const GameBoard& currentBoard, int row, int col){
    GameBoard newBoard = currentBoard;
    int value = currentBoard.grid[row][col+1];
    if(value == 1){ value = 3; }
    else if(value == 2){ value = 4; }
    else if(value == 3){ value = 2; }
    else if(value == 4){ value = 1; }
    newBoard.grid[row][col] = value;
    newBoard.grid[row][col+1] = 0;
    return newBoard;
}

uint8_t visited[40353600] = {0};
uint64_t parent[40353600];

vector<char> solve(const GameBoard& initialBoard){
    int count = 0;
    queue<GameBoard> q;
    q.push(initialBoard);
    visited[board_order(initialBoard)] = 'S';
    while(!q.empty()){
        GameBoard currentBoard = q.front();
        q.pop();
        if(is_valid(currentBoard)){
            vector<char> moves;
            int order = board_order(currentBoard);
            while(visited[order] != 'S'){
                moves.push_back(visited[order]);
                order = parent[order];
            }
            std::reverse(moves.begin(), moves.end());
            display_board(currentBoard);
            return moves;
        }

        auto spacePosition = find_empty_space(currentBoard);
        int row = spacePosition.first;
        int col = spacePosition.second;
        GameBoard moveUp, moveDown, moveLeft, moveRight;
        if(row != 0){
            moveUp = move_up(currentBoard, row, col);
            int order = board_order(moveUp);
            if (!visited[order]) {
                visited[order] = 'U';
                parent[order] = board_order(currentBoard);
                q.push(moveUp);
                count++;
            }
        }
        if(row != 2){
            moveDown = move_down(currentBoard, row, col);
            int order = board_order(moveDown);
            if (!visited[order]) {
                visited[order] = 'D';
                parent[order] = board_order(currentBoard);
                q.push(moveDown);
                count++;
            }
        }
        if(col != 0){
            moveLeft = move_left(currentBoard, row, col);
            int order = board_order(moveLeft);
            if (!visited[order]) {
                visited[order] = 'L';
                parent[order] = board_order(currentBoard);
                q.push(moveLeft);
                count++;
            }
        }
        if(col != 2){
            moveRight = move_right(currentBoard, row, col);
            int order = board_order(moveRight);
            if (!visited[order]) {
                visited[order] = 'R';
                parent[order] = board_order(currentBoard);
                q.push(moveRight);
                count++;
            }
        }
    }
    vector<char> noSolution;
    noSolution.push_back(0);
    return noSolution;
}

void read_game_board(GameBoard& gameBoard){
    for(int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            if(row * col == 1){
                gameBoard.grid[row][col] = 0;
            }
            else{
                int value = 2;
                // cin>>value;
                assert(value != 0);
                gameBoard.grid[row][col] = value;
            }
        }
    }
}

int main(){
    GameBoard initialBoard;
    read_game_board(initialBoard);

    cout << endl << "initial board" << endl;
    display_board(initialBoard);

    cout << endl << "final solved board" << endl;
    auto moves = solve(initialBoard);
    cout << endl;
    if(moves[0] == 0){
        cout << "The board is unsolvable";
    }

    cout << "Required move for empty space to reach final results : " << endl;
    for(char move : moves){
        cout << move << " -> ";
    }
    return  0;
}
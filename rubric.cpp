#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

// Representation of the 2x2x2 Rubik's Cube
using CubeConfiguration = vector<vector<string>>;

// Define the solved state
CubeConfiguration solvedCubeConfig = {  
    {"G", "Y", "O"}, {"B", "O", "Y"},
    {"G", "O", "W"}, {"B", "W", "O"},
    {"G", "R", "Y"}, {"B", "Y", "R"},
    {"G", "W", "R"}, {"B", "R", "W"}
};

// Define the possible moves
enum CubeMove { R, U, F, RIGHT_INV, UP_INV, FRONT_INV, R2, U2, F2 };

// Function to apply a move to the cube state
void applyMoveToCubeConfig(CubeConfiguration &c, CubeMove move) {
    switch (move) {
        case R:
            swap(c[3][1], c[2][2]);
            swap(c[2][2], c[6][1]);
            swap(c[6][1], c[7][2]);
            swap(c[3][0], c[2][1]);
            swap(c[2][1], c[6][0]);
            swap(c[6][0], c[7][1]);
            swap(c[3][2], c[2][0]);
            swap(c[2][0], c[6][2]);
            swap(c[6][2], c[7][0]);
            break;
        case U:
            swap(c[1][1], c[0][2]);
            swap(c[0][2], c[2][1]);
            swap(c[2][1], c[3][2]);
            swap(c[1][2], c[0][0]);
            swap(c[0][0], c[2][2]);
            swap(c[2][2], c[3][0]);
            swap(c[1][0], c[0][1]);
            swap(c[0][1], c[2][0]);
            swap(c[2][0], c[3][1]);
            break;
        case F:
            swap(c[2], c[0]);
            swap(c[0], c[4]);
            swap(c[4], c[6]);
            break;
        case RIGHT_INV:
            swap(c[2][2], c[3][1]);
            swap(c[3][1], c[7][2]);
            swap(c[7][2], c[6][1]);
            swap(c[2][1], c[3][0]);
            swap(c[3][0], c[7][1]);
            swap(c[7][1], c[6][0]);
            swap(c[2][0], c[3][2]);
            swap(c[3][2], c[7][0]);
            swap(c[7][0], c[6][2]);
            break;
        case UP_INV:
            swap(c[0][2], c[1][1]);
            swap(c[1][1], c[3][2]);
            swap(c[3][2], c[2][1]);
            swap(c[0][1], c[1][0]);
            swap(c[1][0], c[3][1]);
            swap(c[3][1], c[2][0]);
            swap(c[0][0], c[1][2]);
            swap(c[1][2], c[3][0]);
            swap(c[3][0], c[2][2]);
            break;
        case FRONT_INV:
            swap(c[0], c[2]);
            swap(c[2], c[6]);
            swap(c[6], c[4]);
            break;
        case R2:
            applyMoveToCubeConfig(c, R);
            applyMoveToCubeConfig(c, R);
            break;
        case U2:
            applyMoveToCubeConfig(c, U);
            applyMoveToCubeConfig(c, U);
            break;
        case F2:
            applyMoveToCubeConfig(c, F);
            applyMoveToCubeConfig(c, F);
            break;
        default:
            cout << "Invalid move!" << endl;
            break;
    }
}

// Function to print the sequence of moves
void printCubeMoves(const vector<CubeMove> &moves) {
    for (const auto &move : moves) {
        switch (move) {
            case R:
                cout << "R ";
                break;
            case U:
                cout << "U ";
                break;
            case F:
                cout << "F ";
                break;
            case RIGHT_INV:
                cout << "R' ";
                break;
            case UP_INV:
                cout << "U' ";
                break;
            case FRONT_INV:
                cout << "F' ";
                break;
            case R2:
                cout << "R2 ";
                break;
            case U2:
                cout << "U2 ";
                break;
            case F2:
                cout << "F2 ";
                break;
        }
    }
    cout << endl;
}

// Function to check if the cube is in the solved state
bool isCubeSolved(const CubeConfiguration &c) {
    return c == solvedCubeConfig;
}

// Encoding the cube state
string serializeCubeConfig(const CubeConfiguration &c) {
    string serialized;
    for (const auto &row : c) {
        for (const auto &color : row) {
            serialized += color;
        }
    }
    return serialized;
}

// BFS algorithm to solve the Rubik's Cube
vector<CubeMove> solveRubiksCubeBFS(const CubeConfiguration &iniCube) {
    queue<pair<CubeConfiguration, vector<CubeMove>>> q;

    unordered_set<string> visited;

    q.push({iniCube, {}});

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        const CubeConfiguration &currCube = curr.first;
        const vector<CubeMove> &currMoves = curr.second;

        // Check if the current state is the goal state
        if (isCubeSolved(currCube)) {
            return currMoves;
        }

        string serializedConfig = serializeCubeConfig(currCube);

        if (visited.find(serializedConfig) == visited.end()) {
            visited.insert(serializedConfig);

            // Iterate through possible moves
            for (int move = R; move <= F2; ++move) {
                CubeConfiguration nextCube = currCube;
                applyMoveToCubeConfig(nextCube, static_cast<CubeMove>(move));

                vector<CubeMove> nextMoves = currMoves;
                nextMoves.push_back(static_cast<CubeMove>(move));
                q.push({nextCube, nextMoves});
            }
        }
    }

    return {};
}

// Function to print the CubeConfiguration
void printCubeConfig(const CubeConfiguration &c) {
    for (const auto &row : c) {
        for (const auto &color : row) {
            cout << color << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {

    CubeConfiguration solvCubeConfig = {
        {"G", "Y", "O"}, {"B", "O", "Y"},
        {"G", "O", "W"}, {"B", "W", "O"},
        {"G", "R", "Y"}, {"B", "Y", "R"},
        {"G", "W", "R"}, {"B", "R", "W"}
    };                                              // solved cube configuration : 
                                                    // initial and required move should be done by facing the orange color in cube


    cout << endl << "solved cube configuration" << endl;
    printCubeConfig(solvCubeConfig);





    const int rows = 8;
    const int columns = 3;
  
    vector<vector<string>> iniCubeConfig(rows, vector<string>(columns, ""));

    // Take input for the structure
    cout << "Give the scrambled cube configuration:" << endl;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
                cin >> iniCubeConfig[i][j];
        }
    }


    // // applying random moves to initial cube configuration (solved cube)
    // applyMoveToCubeConfig(iniCubeConfig, R);
    // applyMoveToCubeConfig(iniCubeConfig, U2);
    // applyMoveToCubeConfig(iniCubeConfig, FRONT_INV);
    // applyMoveToCubeConfig(iniCubeConfig, R2);
    // applyMoveToCubeConfig(iniCubeConfig, U);
    // applyMoveToCubeConfig(iniCubeConfig, F2);
    
    // cout << endl << "scrambled cube Configuration" << endl;
    // printCubeConfig(iniCubeConfig);

    vector<CubeMove> solution = solveRubiksCubeBFS(iniCubeConfig);

    if (!solution.empty()) {
        cout << endl << "Required Move to solve the cube :   ";
        printCubeMoves(solution);
        cout << endl;
    } else {
        cout << "Invalid Cube" << endl;
    }

    return 0;
}
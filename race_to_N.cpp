#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class RaceToNGame {
private:
    int targetN;
    int minAdd;
    int maxAdd;
    int currentPosition;
    bool gameOver;
    string winner;
    vector<int> keyPositions;
    int gameMode;
    
    void computeKeyPositions() {
        int modulus = maxAdd + 1;
        int targetMod = targetN % modulus;
        
        if (targetMod == 0) {
            for (int i = modulus; i <= targetN; i += modulus) {
                keyPositions.push_back(i);
            }
        } else {
            for (int i = targetMod; i <= targetN; i += modulus) {
                keyPositions.push_back(i);
            }
        }
    }
    
    int bestMove(int sum) {
        // Find the next key position to move to
        for (int i = 0; i < keyPositions.size(); i++) {
            if (sum == keyPositions[i]) {
                // Already at key position, make any valid move
                return rand() % maxAdd + minAdd;
            }
            
            if (sum < keyPositions[i]) {
                int move = keyPositions[i] - sum;
                if (move >= minAdd && move <= maxAdd) {
                    return move;
                }
                // If can't reach directly, make random move
                break;
            }
        }
        
        // No optimal move, make random valid move
        return rand() % maxAdd + minAdd;
    }
    
    string getPlayerName(int playerNum) {
        if (gameMode == 1) {
            return (playerNum == 1) ? "You" : "Opponent";
        } else if (gameMode == 2) {
            return (playerNum == 1) ? "You" : "AI";
        } else {
            return (playerNum == 1) ? "AI" : "You";
        }
    }
    
    bool isAIPlayer(int playerNum) {
        if (gameMode == 1) return false;
        if (gameMode == 2) return playerNum == 2;
        return playerNum == 1;
    }
    
public:
    RaceToNGame(int target, int minRange, int maxRange, int mode) 
        : targetN(target), minAdd(minRange), maxAdd(maxRange), 
          currentPosition(0), gameOver(false), gameMode(mode) {
        srand(time(0));
        computeKeyPositions();
    }
    
    void displayGameState(int player, bool isAI) {
        cout << "\nCurrent Position: " << currentPosition << " / " << targetN << "\n";
        if (isAI) {
            cout << getPlayerName(player) << " is thinking...\n";
        } else {
            cout << getPlayerName(player) << "'s turn\n";
            cout << "Add a number between " << minAdd << " and " << maxAdd << ": ";
        }
    }
    
    bool makeMove(int player, int moveAmount) {
        if (moveAmount < minAdd || moveAmount > maxAdd) {
            cout << "Invalid move! Must be between " << minAdd << " and " << maxAdd << "\n";
            return false;
        }
        
        int newPosition = currentPosition + moveAmount;
        
        if (newPosition > targetN) {
            cout << "Invalid move! Would exceed target " << targetN << "\n";
            return false;
        }
        
        currentPosition = newPosition;
        cout << getPlayerName(player) << " adds " << moveAmount 
             << " -> Position: " << currentPosition << "\n";
        
        if (currentPosition == targetN) {
            gameOver = true;
            winner = getPlayerName(player);
            return true;
        }
        
        return true;
    }
    
    int getAIMove() {
        return bestMove(currentPosition);
    }
    
    void displayWinner() {
        cout << "\nGAME OVER! " << winner << " WINS!\n";
        cout << "Final Position: " << currentPosition << "\n";
    }
    
    bool isGameOver() { 
        return gameOver; 
    }
    
    void displayStrategy() {
        cout << "\nKey Winning Positions: ";
        for (int pos : keyPositions) {
            cout << pos << " ";
        }
        cout << "\n\n";
    }
    
    bool checkIfAI(int player) {
        return isAIPlayer(player);
    }
};

void playGame(RaceToNGame& game) {
    int currentPlayer = 1;
    
    while (!game.isGameOver()) {
        bool isAI = game.checkIfAI(currentPlayer);
        game.displayGameState(currentPlayer, isAI);
        
        if (isAI) {
            int aiMove = game.getAIMove();
            game.makeMove(currentPlayer, aiMove);
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        } else {
            int move;
            cin >> move;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }
            
            if (game.makeMove(currentPlayer, move)) {
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        }
    }
    
    game.displayWinner();
}

int main() {
    cout << "RACE TO N GAME\n\n";
    
    int target, minRange, maxRange;
    
    cout << "Enter target number N: ";
    cin >> target;
    
    cout << "Enter minimum add per turn: ";
    cin >> minRange;
    
    cout << "Enter maximum add per turn: ";
    cin >> maxRange;
    
    if (target <= 0 || minRange < 1 || maxRange < minRange) {
        cout << "Invalid parameters!\n";
        return 1;
    }
    
    cout << "\nGAME MODE:\n";
    cout << "1. You vs Opponent\n";
    cout << "2. You vs AI (You first)\n";
    cout << "3. AI vs You (AI first)\n";
    cout << "Choice: ";
    
    int mode;
    cin >> mode;
    
    if (mode < 1 || mode > 3) {
        cout << "Invalid mode!\n";
        return 1;
    }
    
    RaceToNGame game(target, minRange, maxRange, mode);
    
    // game.displayStrategy();
    
    cout << "START\n";
    playGame(game);
    
    return 0;
}

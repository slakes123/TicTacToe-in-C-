// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

class Player {
private:
    char symbol;
    string name;


public:
    Player(char sym = 'X', string n = "Player X") : symbol(sym), name (n) {}

    char getSymbol() const { return symbol; }
    string getName() const { return name; }

};

class Board {
private:
    char grid[3][3];
    int filledCells;

public:
    Board() : filledCells(0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                grid[i][j] = ' ';
            }
        }
    }

    void drawBoard() const {
        cout << "-------" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "|";
            for (int j = 0; j < 3; j++) {
                cout << grid[i][j] << "|";
            }
            cout << endl << "-------" << endl;
        }
    }

    bool isMoveValid(int row, int col) {
        return (row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col] == ' ');
    }

    void makeMove(int row, int col, char sym) {
        if (isMoveValid(row, col)) {
            grid[row][col] = sym;
            filledCells++;
        }
    }

    bool checkWin(char sym) {
        // Checks rows for a win
        for (int i = 0; i < 3; i++) {
            if (grid[0][i] == sym && grid[1][i] == sym && grid[2][i] == sym) {
                return true;
            }
        }
        // Check coloums for a win 
        for (int i = 0; i < 3; i++) {
            if (grid[i][0] == sym && grid[i][1] == sym && grid[i][2] == sym) {
                return true;
            }
        }
        // Check diagnols for a win
        if (grid[0][0] == sym && grid[1][1] == sym && grid[2][2] == sym) {
            return true;
        }
        if (grid[0][2] == sym && grid[1][1] == sym && grid[2][0]) {
            return true;
        }

        return false;
    }

    bool isBoardFull() const {
        return filledCells == 9;
    }

    int getFilledCellCount() const {
        return filledCells;
    }
};

class TicTacToe {
private:
    Board board;
    Player players[2];
    int currPlayerIndex;

public:
    TicTacToe() : currPlayerIndex(0) {
        players[0] = Player('X', "Player X");
        players[1] = Player('O', "Player O");
    }

    Player& getCurrPlayer() {
        return players[currPlayerIndex];

    }

    void switchTurn() {
        currPlayerIndex = (currPlayerIndex + 1) % 2;

    }

    void play() {
        int row, col;

        cout << "Welcome to Tic Tac Toe \n";

        while (!board.isBoardFull()) {

            board.drawBoard();

            Player& currPlayer = getCurrPlayer();

            while (true) {
                cout << currPlayer.getName() << " (" << currPlayer.getSymbol() << "), enter row (1-3) and column (1-3): ";
                cin >> row >> col;
                row--;
                col--;

                if (board.isMoveValid(row, col)) {
                    break;
                }
                else {
                    cout << "Invalid Move.";
                }
            }

            board.makeMove(row, col, currPlayer.getSymbol());

            if (board.checkWin(currPlayer.getSymbol())) {
                board.drawBoard();

                cout << currPlayer.getName() << " Wins!!" << endl;
                return;
            }

            switchTurn();
        }

        board.drawBoard();
        cout << "No One Wins!";
    }
};

int main()
{
    TicTacToe game;

    game.play();

    return 0;
}

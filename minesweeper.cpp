#include <iostream>
#include <string.h>
#include <chrono>
#include <random>
using namespace std;

const int cellsMX = 25, minesMX = 99, movesMX = 526;
int cells, Mines;

bool validCell(int r, int c) {
    return (r >= 0 && r <= cells) && (c >= 0 && c <= cells);
}

bool mineCell(int r, int c, char board[][cellsMX]) {
    return (board[r][c] == '*');
}

bool validMineCheck(int r, int c, char board[][cellsMX]) {
    if (validCell(r,c))
        return mineCell(r,c,board);
}

void userMove(int *r, int *c) {
    cout << "Enter your move (row, column):\n";
    scanf("%d %d", r, c);
    cout << "\n";
    return;
}

void outputBoard(char userBoard[][cellsMX]) {
    
    if (cells < 10) {
        cout << "  ";
        for (int i = 1; i <= cells; i++) {
            cout << i << " ";
        }
        cout << endl;
        for (int i = 1; i <= cells; i++) {
            cout << i;
            for (int j = 0; j < cells; j++) {
                cout << " " << userBoard[i-1][j]; 
            }
            cout << endl;
        }
        return;

    } else {
        cout << "    ";
        for (int i = 1; i <= cells; i++) {
            if (i < 10) cout << i << "   ";
            else cout << i << "  ";
        }
        cout << endl;
        for (int i = 1; i <= cells; i++) {
            if (i < 10) {
                cout << " " << i << "  ";
            } else {
                cout << i << "  ";
            }
            for (int j = 0; j < cells; j++) {
                cout << userBoard[i-1][j] << "   ";
            }
            cout << "\n\n";
        }
        
        return;
    }
    
}

int adjMineCount(int r, int c, int mines[][2], char gameBoard[][cellsMX]) {
    int cnt = 0;
    
    if (validMineCheck(r+1, c, gameBoard)) cnt++;
    if (validMineCheck(r-1, c, gameBoard)) cnt++;
    if (validMineCheck(r, c+1, gameBoard)) cnt++;
    if (validMineCheck(r, c-1, gameBoard)) cnt++;
    if (validMineCheck(r+1, c+1, gameBoard)) cnt++;
    if (validMineCheck(r+1, c-1, gameBoard)) cnt++;
    if (validMineCheck(r-1, c+1, gameBoard)) cnt++;
    if (validMineCheck(r-1, c-1, gameBoard)) cnt++;

    return(cnt);

}

bool gameUtil(char userBoard[][cellsMX], char gameBoard[][cellsMX],
            int mines[][2], int r, int c, int *mleft) {

    if (userBoard[r][c] != '-') return false;
    
    if (gameBoard[r][c] == '*') {
        userBoard[r][c] == '*';
        
        for (int i = 0; i < Mines ; i++) {
            userBoard[mines[i][0]][mines[i][1]] = '*';
        }

        outputBoard(userBoard);
        cout << "\nYou Lost!\n";
        return (true);

    } else {

        int cnt = adjMineCount(r, c, mines, gameBoard);
        (*mleft)--;
        
        userBoard[r][c] = cnt + '0';

        if (!cnt) {

            if (validCell(r-1, c)) {
                if (!mineCell(r-1, c, gameBoard))
                    gameUtil(userBoard, gameBoard, mines, r-1, c, mleft);

            }

            if (validCell(r+1, c)) {
                if (!mineCell(r+1, c, gameBoard))
                    gameUtil(userBoard, gameBoard, mines, r+1, c, mleft);

            }

            if (validCell(r, c+1)) {
                if (!mineCell(r, c+1, gameBoard))
                    gameUtil(userBoard, gameBoard, mines, r, c+1, mleft);

            }

            if (validCell(r, c-1)) {
                if (!mineCell(r, c-1, gameBoard))
                    gameUtil(userBoard, gameBoard, mines, r, c+1, mleft);

            }

            if (validCell(r+1, c+1)) {
                if (!mineCell(r+1, c+1, gameBoard))
                    gameUtil(userBoard, gameBoard, mines, r+1, c+1, mleft);

            }

            if (validCell(r+1, c-1)) {
                if (!mineCell(r+1, c-1, gameBoard))
                    gameUtil(userBoard, gameBoard, mines, r+1, c-1, mleft);

            }

            if (validCell(r-1, c+1)) {
                if (!mineCell(r-1, c+1, gameBoard))
                    gameUtil(userBoard, gameBoard, mines, r-1, c+1, mleft);

            }

            if (validCell(r-1, c-1)) {
                if (!mineCell(r-1, c-1, gameBoard))
                    gameUtil(userBoard, gameBoard, mines, r-1, c-1, mleft);

            }

        }

        return false;

    }

}

void genMines(int mines[][2], char gameBoard[][cellsMX]) {

    default_random_engine generator;
    uniform_int_distribution<int> distribution(0,cells);

    for (int i = 0; i < Mines;) {
        int r = distribution(generator);
        int c = distribution(generator);
        
        mines[i][0] = r;
        mines[i][1] = c;

        gameBoard[mines[i][0]][mines[i][1]] = '*';
        i++;

    }
   
    return;

}

void initialiseGame(char gameBoard[][cellsMX], char userBoard[][cellsMX]) {
    srand(time (NULL));

    for (int i=0; i < cells; i++) {
        for (int j = 0; j < cells; j++) {
            userBoard[i][j] = gameBoard[i][j] = '-';
        }
    }
}

void repMine(int r, int c, char board[][cellsMX]) {
    for (int i = 0; i < cells; i++) {
        for (int j = 0; j < cells; j++) {
            if (board[i][j] != '*') {
                board[i][j] = '*';
                board[r][c] = '-';
                return;
            }
        }
    }
}

void Minesweeper() {
    bool gameDone = false;

    char gameBoard[cellsMX][cellsMX], userBoard[cellsMX][cellsMX];
    int mleft = cells * cells - Mines, r, c;
    int mines[minesMX][2];
    int moves[movesMX][2];

    initialiseGame(gameBoard, userBoard);
    genMines (mines, gameBoard);

    int currMove = 0;

    while (!gameDone) {
        cout << "\nCurrent Status of Board:\n\n";
        
        outputBoard(userBoard);
        userMove(&r, &c);
        r--; c--;

        if (currMove == 0) {
            if (mineCell(r,c,gameBoard)) repMine(r,c,gameBoard);
        }

        currMove++;

        gameDone = gameUtil(userBoard, gameBoard, mines, r, c, &mleft);

        if (!gameDone && (mleft == 0)) {
            cout << "\nYou won!\n";
            gameDone = true;
        }
    }

    return;

}

void chooseDifficulty() {

    int level;

    cout << "Choose one of the following options:\n" <<
            "(1) BEGINNER --> 9x9 board, 24 mines\n" <<
            "(2) INTERMEDIATE --> 16x16 board, 40 mines\n" <<
            "(3) EXPERT --> 24x24 board, 99 mines\n\n";
    
    cin >> level;
    
    if (level == 1) {
        cells = 9;
        Mines = 24;
    } else if (level == 2) {
        cells = 16;
        Mines = 40;
    } else if (level == 3) {
        cells = 24;
        Mines = 99;
    }

}

int main() {

    cout << "Welcome to Minesweeper!\n\n";

    chooseDifficulty();
    Minesweeper();
    
    system("pause");

}
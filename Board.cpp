#include <iostream>
#include <iomanip>
#include <cctype>
#include <climits>
#include "Board.h"
using namespace std;

Board::Board() {
    char *ptr = arr[0];
    for (int i = 0; i < ROW * COLUMN; i++) {
        *ptr = ' ';
        ptr++;
    }
}
void Board::PrintArr(void) {
    cout << "+---+---+---+---+---+---+---+" << endl;
    for (int i = 0; i < ROW; i++) {
        cout << "|";
        for (int j = 0; j < COLUMN; j++) {
            cout << setw(2) << arr[i][j] << setw(2) << "|";
        }
        cout << endl;
        cout << "+---+---+---+---+---+---+---+" << endl;
    }
    cout << "  0   1   2   3   4   5   6" << endl;
}
void Board::Insert(bool turn_) {
    int num, i = ROW - 1;
    turn_ ? cout << "Player O >> " : cout << "Player X >> ";
    cin >> num;
    // Monkey test
    while (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "INvalid input, try again [0, 6]." << endl;
        turn_ ? cout << "Player O >> " : cout << "Player X >> ";
        cin >> num;
    }
    while (!Monkey(num)) {
        turn_ ? cout << "Player O >> " : cout << "Player X >> ";
        cin >> num;
    }

    while(arr[i][num] != ' ') {
        i--;
    }

    turn_ ? arr[i][num] = 'O' : arr[i][num] = 'X';
}
bool Board::Monkey(int num_) {
    if (num_ < 0 || num_ > 6) {
        cout << "Invalid input, try again [0, 6]." << endl;
        return false;
    } else if (arr[0][num_] != ' ') {
        cout << "This column is full. Try another column." << endl;
        return false;
    }
    return true;
}
bool Board::Check(bool turn_) {
    bool judgment = false;

    // row
    horizontal:;
        for (int row = 0; row < ROW; row++) {   // The row number
            for (int col = 0; col <= COLUMN - 4; col++) {    // The column number
                char *check = &arr[row][col];
                if (*check == ' ') {
                    continue;
                }
                int continuity = 1;
                char _col = col + 1;
                while (_col < COLUMN) {
                    if (toupper(arr[row][_col]) == toupper(*check)) {
                        continuity++;
                        _col++;
                        continue;
                    } else {
                        break;
                    }
                }
                _col = col;
                if (continuity >= 4) {
                    for (int i = 0; i < continuity; i++) {
                        arr[row][_col] = tolower(arr[row][_col]);
                        _col++;
                    }
                    judgment = true;
                    goto vertical;
                }
            }
        }

    // column
    vertical:;
        for (int col = 0; col < COLUMN; col++) {   // The row number
            for (int round = ROW - 4; round >= 0; round--) {  // The round steps needs
                char *check = &arr[round][col];
                if (*check == ' ') {
                    continue;
                }
                int row;
                for (row = round + 1; row < round + 4; row++) {
                    if (toupper(arr[row][col]) == toupper(*check)) {
                        continue;
                    } else {
                        break;
                    }
                }
                if (row == round + 4) {  // If row reach the last elements in the round
                    for (int i = 0; i < 4; i++) {
                        *check = tolower(*check);
                        check += COLUMN;
                    }
                    judgment = true;  
                    goto diagonal;
                }
            }
        }
    // Diagonal
    diagonal:;
        // From upper left to lower right
        for (int row = 0; row < ROW - 4 + 1; row++) {
            for (int col = 0; col < COLUMN - 4 + 1; col++) {
                char *check = &arr[row][col];
                if (*check == ' ') {
                    continue;
                }
                char *ptr = check + COLUMN + 1;
                int continuity = 1;
                while (ptr - arr[0] < ROW * COLUMN) {
                    if (toupper(*ptr) == toupper(*check)) {
                        continuity++;
                        ptr += COLUMN + 1;
                        continue;
                    } else { 
                        break;
                    }
                }
                ptr = check;
                if (continuity >= 4) {
                    for (int i = 0; i < continuity; i++) {
                        *ptr = tolower(*ptr);
                        ptr += COLUMN + 1;
                        
                    }
                    judgment = true;
                }
            }
        }

        // From upper right to lower left
        for (int row = 0; row < ROW - 4 + 1; row++) {
            for (int col = 3; col < COLUMN; col++) {
                char *check = &arr[row][col];
                if (*check == ' ') {
                    continue;
                }
                int _row = row + 1, _col = col - 1;
                int continuity = 1;
                while (_row < ROW && _col >= 0) {
                    if (toupper(arr[_row][_col]) == toupper(*check)) {
                        continuity++;
                        _row++;
                        _col--;
                    } else {
                        break;
                    }
                }
                _row = row, _col = col;
                if (continuity >= 4) {
                    for (int i = 0; i < continuity; i++) {
                        arr[_row][_col] = tolower(arr[_row][_col]);
                        _row++;
                        _col--;
                    }
                    judgment = true;
                }
            }
        }

    // Draw
    draw:;
        char *ptr = &arr[0][0];
        int i;
        for (i = 0; i < ROW * COLUMN; i++) {
            if (*ptr == ' ') {
                break;
            }
            ptr++;
        }
        if (i == ROW * COLUMN) {
            PrintArr();
            cout << "Draw" << endl;
            judgment = true;
            return judgment;
        }
    
    if (judgment) {
        PrintArr();
        !turn_ ? cout << "Winner: O" << endl : cout << "Winner: X" << endl;
    }
    

    return judgment;
}
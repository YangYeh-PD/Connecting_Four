#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>  // For using toupper() and tolower()
#define COLUMN 7
#define ROW 6

void initialized(char*);
void print_board(char*);
bool insert(const int ,const char);
bool judge(void);
int min(int, int);

char board[ROW][COLUMN];
bool turn = false;   /* true => O False => X */

int main(int argc, char *argv[]) {
    int column;
    initialized(board[0]);

    while (!judge()) {
        turn = !turn;
        if (turn) {
            printf("Player O >> ");
            scanf("%d", &column);
            while (!insert(column, 'O')) {
                printf("Player O >> ");
                scanf("%d", &column);
            }
        } else {
            printf("Player X >> ");
            scanf("%d", &column);
            while (!insert(column, 'X')) {
                printf("Player X >> ");
                scanf("%d", &column);
            }
        }
    }

    turn ? printf("Winner: O\n") : printf("Winner: X\n");
    return 0;
}

/* The function that initializing the board */
void initialized(char *ch) {
    for (int i = 0; i < ROW * COLUMN; i++) {
        *ch = ' ';
        ch++;
    }
}

/* The function that print out the game board */
void print_board(char *ch) {
    for (int i = 0; i < ROW; i++) {
        printf("+---+---+---+---+---+---+---+\n");
        printf("|");
        for (int j = 0; j < COLUMN; j++) {
            printf(" %c |", *ch);
            ch++;
        }
        printf("\n");
    }
    printf("+---+---+---+---+---+---+---+\n");
    printf("  0   1   2   3   4   5   6\n");
}

bool insert(const int number, const char ch) {
    int row;

    /* Monkey Test */
    if (number < 0 || number > 6) {
        printf("Invalid input, try again [0, 6].\n");
        while (getchar() != '\n');  /* Clear the keyboard input buffer */
        return false;
    }
    for (row = ROW - 1; row >= 0; row--) {
        if (board[row][number] == 32) {
            board[row][number] = ch;
            return true;
        }
    }
    printf("This column is full. Try another column.\n");
    return false;
}

bool judge(void) {
    bool judgment = false;
    
    horizontal: ;
        for (int row = 0; row < ROW; row++) {   // The row number
            for (int col = 0; col <= COLUMN - 4; col++) {    // The column number
                char *check = &board[row][col];
                if (*check == ' ') {
                    continue;
                }
                int continuity = 1;
                char _col = col + 1;
                while (_col < COLUMN) {
                    if (toupper(board[row][_col]) == toupper(*check)) {
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
                        board[row][_col] = tolower(board[row][_col]);
                        _col++;
                    }
                    judgment = true;
                    goto vertical;
                }
            }
        }
    
    vertical: ;
        for (int col = 0; col < COLUMN; col++) {   // The row number
            for (int round = ROW - 4; round >= 0; round--) {  // The round steps needs
                char *check = &board[round][col];
                if (*check == ' ') {
                    continue;
                }
                int row;
                for (row = round + 1; row < round + 4; row++) {
                    if (toupper(board[row][col]) == toupper(*check)) {
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

    diagonal: ;
        // From upper left to lower right
        for (int row = 0; row < ROW - 4 + 1; row++) {
            for (int col = 0; col < COLUMN - 4 + 1; col++) {
                char *check = &board[row][col];
                if (*check == ' ') {
                    continue;
                }
                char *ptr = check + COLUMN + 1;
                int continuity = 1;
                while (ptr - board[0] < ROW * COLUMN) {
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
                char *check = &board[row][col];
                if (*check == ' ') {
                    continue;
                }
                int _row = row + 1, _col = col - 1;
                int continuity = 1;
                while (_row < ROW && _col >= 0) {
                    if (toupper(board[_row][_col]) == toupper(*check)) {
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
                        board[_row][_col] = tolower(board[_row][_col]);
                        _row++;
                        _col--;
                    }
                    judgment = true;
                }
            }
        }

    draw: ;
        char *ptr = &board[0][0];
        int i;
        for (i = 0; i < ROW * COLUMN; i++) {
            if (*ptr == ' ') {
                break;
            }
            ptr++;
        }
        if (i == ROW * COLUMN) {
            printf("Draw\n");
            judgment = true;
            return judgment;
        }

    print_board(board[0]);
    return judgment;
}

int min(int x, int y) {
    return x < y ? x : y;
}
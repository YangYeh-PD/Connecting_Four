#include <iostream>
#include "Board.h"
using namespace std;

int main(int argc, char *argv[]) {
    // Making a game board and initializing
    bool turn = true; // true = O ; false = X
    Board game;
    game.PrintArr();

    while (!game.Check(turn)) {
        if (turn) {
            game.Insert(turn);
            turn = false;
            game.PrintArr();
        } else {
            game.Insert(turn);
            turn = true;
            game.PrintArr();
        }
    }
    
    return 0;
}
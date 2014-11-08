#ifndef TICTACTOEBOARD_H
#define TICTACTOEBOARD_H

#include "cell.h"
#include "move.h"
#include "transmitter.h"
#include <vector>
#include <array>

class TicTacToeBoard{ // I think here are the main problem
public:
    TicTacToeBoard(int row, int col);
    TicTacToeBoard(const TicTacToeBoard& other);

    bool operator!=(const TicTacToeBoard& other);

    TicTacToeBoard& clone();
    bool isFull();

    std::vector<Cell> getEmptyCells();
    bool playCellSilently(int row, int col, int player);
    bool playCell(int row, int col, int player);
    bool checkWon(int row, int col, bool silent);

    int row;
    int col;
    int winner;

    Cell cells[3][3];

    Transmitter *transit;

    int slot1[2];
    int slot2[2];
    int slot3[2];

    std::vector<Move> wonSlots;

};

#endif // TICTACTOEBOARD_H

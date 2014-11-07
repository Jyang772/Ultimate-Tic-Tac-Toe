#ifndef TICTACTOEBOARD_H
#define TICTACTOEBOARD_H

#include "cell.h"
#include <vector>

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
    bool checkWon(int row, int col);

    int row;
    int col;
    int winner;

    Cell cells[3][3];
};

#endif // TICTACTOEBOARD_H

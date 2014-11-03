#ifndef TICTACTOEBOARD_H
#define TICTACTOEBOARD_H

#include "cell.h"
#include "board.h"

#include <vector>


class TicTacToeBoard
{
public:
    TicTacToeBoard(){}
    TicTacToeBoard(int row, int col);
    TicTacToeBoard clone();


    bool isFull();
    bool checkWon(int row, int col);
    void getEmptyCells(std::vector<Cell> &validCells);
    bool playCell(int row, int col, int player);
    bool playCellSilently(int row, int col, int player);

    bool operator!=(const TicTacToeBoard&);

    int row;
    int col;
    int winner = -99;

    Cell *cells[3][3];
};

#endif // TICTACTOEBOARD_H

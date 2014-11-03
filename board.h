#ifndef BOARD_H
#define BOARD_H
#include "cell.h"
#include <vector>

class Board{

public:
    Board(){}
    Board(int row, int col);
    bool isFull();

    void getEmptyCells(std::vector<Cell> validCells);

    int row;
    int col;
    int winner;

    Cell *cells[3][3];

};
#endif // BOARD_H

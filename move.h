#ifndef MOVE_H
#define MOVE_H

struct Move{
    Move(){};
    Move(int bRow, int bCol, int cRow, int cCol) : bRow(bRow), bCol(bCol), cRow(cRow), cCol(cCol){}

    int bRow;
    int bCol;

    int cRow;
    int cCol;
};
#endif // MOVE_H

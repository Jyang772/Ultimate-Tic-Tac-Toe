#ifndef CELL_H
#define CELL_H

class Cell{
public:
    Cell(int row, int col);
    void playCell(int owner);

    Cell clone();


    int row;
    int col;
    int owner;
    int winner;
};

#endif // CELL_H

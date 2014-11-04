#ifndef CELL_H
#define CELL_H

class Cell{
public:
    Cell(int row, int col);
    void playCell(int owner);

    Cell clone();


    int row;
    int col;
    int owner = 0;
    int winner = 0;
};

#endif // CELL_H

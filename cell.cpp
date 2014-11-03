#include "cell.h"

Cell::Cell(int row, int col) : row(row), col(col)
{
}


void Cell::playCell(int owner){
        this->owner = owner;
}

Cell Cell::clone(){
    Cell clone = Cell(this->row, this->col);
    clone.owner = this->owner;
    clone.winner = this->winner;
    return clone;
}

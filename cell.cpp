#include "cell.h"

Cell::Cell(int row, int col) : row(row), col(col)
{
}


void Cell::playCell(int owner){
        this->owner = owner;

    if(!this->owner){
        return;
    }
    if(!this->winner){

    }
}

Cell Cell::clone(){
    Cell clone = Cell(this->row, this->col);
    clone.owner = this->owner;
    clone.winner = this->winner;
    return clone;
}

bool Cell::operator !=(const Cell &other){

    if(row != other.row)
        return true;
    if(col != other.col)
        return true;


    return false;
}

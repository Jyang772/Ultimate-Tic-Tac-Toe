#include "board.h"

Board::Board(int row, int col) : row(row), col(col)
{

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cells[i][j] = new Cell(i,j);
        }

    }
}



bool Board::isFull(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(!cells[i][j]->owner)
                return false;
        }
    }
    return true;
}

void Board::getEmptyCells(std::vector<Cell> validCells){

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){

            if(!this->cells[i][j]->owner){
                validCells.push_back(*this->cells[i][j]);
            }
        }
    }
}

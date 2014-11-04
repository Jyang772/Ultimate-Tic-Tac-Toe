#include "tictactoeboard.h"
#include <QDebug>

TicTacToeBoard::TicTacToeBoard(int row, int col) : row(row), col(col)
{

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cells[i][j] = new Cell(i,j);
        }
    }
}

TicTacToeBoard TicTacToeBoard::clone(){

    TicTacToeBoard *clone = new TicTacToeBoard(row,col);
    clone->winner = winner;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            *clone->cells[i][j] = cells[i][j]->clone();
        }
    }

    return *clone;
}

bool TicTacToeBoard::isFull(){

    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++){
            if(!this->cells[i][j]->owner) {
                return false;
            }
        }
    }
    return true;

}


void TicTacToeBoard::getEmptyCells(std::vector<Cell> &validCells){


    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(!this->cells[i][j]->owner){
                validCells.push_back(*this->cells[i][j]);
            }
        }
    }
}

bool TicTacToeBoard::playCell(int row, int col, int player){

    Cell *cell = cells[row][col];

    if(!cell->owner){
        cell->playCell(player);
        bool won = false;

        if(!winner){
            won = checkWon(row, col);
            if(won){
                winner = player;
                for(int i=0; i<3; i++){
                    for(int j=0; j<3; j++){
                        cells[i][j]->winner = player;
                        //Transmit winning rows, cols
                        //transit->highlight();
                    }
                }
            }
        }
        return won;
    }
    else{
        //ERROR!!
    }
    return false;
}

bool TicTacToeBoard::playCellSilently(int row, int col, int player){

    Cell *cell = cells[row][col];
    cell->owner = player;

    if(!this->winner){
        bool justWon = this->checkWon(row,col);
        if(justWon){
            this->winner = player;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    this->cells[i][j]->winner = player;
                }
            }
        }
        return justWon;
    }
    return false;
}

bool TicTacToeBoard::checkWon(int row, int col){

    int player = this->cells[row][col]->owner;

    int i=0;
    while(i<3 && this->cells[row][i]->owner && this->cells[row][i]->owner == player){
        i+= 1;
    }

    if(i == 3){
        return true;
    }

    //check the column
    i = 0;
    while(i<3 && this->cells[i][col]->owner && this->cells[i][col]->owner == player){
    i+= 1;
    }
    if(i == 3){
        return true;
    }

    //check upper left to lower right diagonal
    i = 0;
    while(i<3 && this->cells[i][i]->owner && this->cells[i][i]->owner == player){
        i+= 1;
    }
    if(i == 3){
        return true;
    }
    //check upper right to lower left diagonal
    i=0;
    while(i<3 && this->cells[i][2-i]->owner && this->cells[i][2-i]->owner == player){
        i+=1;
    }
    if(i == 3){
        return true;
    }

    return false;
}

bool TicTacToeBoard::operator !=(const TicTacToeBoard& board){

    if(&this->cells != &board.cells)
        return false;
    if(this->col != board.col)
        return false;
    if(this->row != board.row)
        return false;
    if(this->winner != board.winner)
        return false;

    return true;
}

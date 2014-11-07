#include "clone.h"


Clone::Clone(int boardRow,int boardCol,int cellRow,int cellCol,Game clone,int wins,double weightedWins,double weightedLosses,double ties){
    this->boardRow = boardRow;
    this->boardCol = boardCol;
    this->cellRow = cellRow;
    this->cellCol = cellCol;
    this->clone = clone;
    this->wins = wins;
    this->weightedWins = weightedWins;
    this->losses = losses;
    this->weightedLosses = weightedLosses;
    this->ties = ties;
}


Clone::Clone(const Clone& other){

    this->boardRow = other.boardRow;
    //    this->boardCol = other.boardRow; // <---- Here was the typo
    this->boardCol = other.boardCol;
    this->cellRow = other.cellRow;
    this->cellCol = other.cellCol;
    this->wins = other.wins;
    this->weightedWins = other.weightedWins;
    this->weightedLosses = other.weightedLosses;
    this->losses = other.losses;
    this->ties = other.ties;

    this->clone = other.clone;
}

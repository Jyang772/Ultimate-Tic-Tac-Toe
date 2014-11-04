#include "clone.h"

Clone::Clone(){

     wins = 0;
     weightedWins = 0;
     losses = 0;
     weightedLosses = 0;
     ties = 0;

}

Clone::Clone(const Clone &other){


    this->boardRow = other.boardRow;
    this->boardCol = other.boardRow;
    this->cellRow = other.cellRow;
    this->cellCol = other.cellCol;
    this->wins = other.wins;
    this->weightedWins = other.weightedWins;
    this->weightedLosses = other.weightedLosses;
    this->losses = other.losses;
    this->ties = other.ties;

    this->clone = other.clone;


}

Clone& Clone::operator =(Clone &other){

    this->boardRow = other.boardRow;
    this->boardCol = other.boardRow;
    this->cellRow = other.cellRow;
    this->cellCol = other.cellCol;
    this->wins = other.wins;
    this->weightedWins = other.weightedWins;
    this->weightedLosses = other.weightedLosses;
    this->losses = other.losses;
    this->ties = other.ties;

    this->clone = other.clone;

}

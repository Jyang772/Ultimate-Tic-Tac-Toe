#include "cell.h"

Cell::Cell(){

}

Cell::Cell(int row, int col):
  owner(0), winner(0) // r: Initalization of members could be done here
{
    this->row = row;
    this->col = col;
    owner = 0;
    winner = 0;
}

Cell::Cell(const Cell& other):
  row(other.row),  // r: As i remember - C++ created default copy constructor
  col(other.col),  // r: itself. No need to define it explicitly. By the way, I will.
  owner(other.owner),
  winner(other.winner)
{ }

bool Cell::operator==(const Cell& other) const{
  return this->row == other.row and \
    this->col == other.col and \
    this->owner == other.owner;
}

bool Cell::operator!=(const Cell& other) const{
  return !(*this == other);
}

const Cell& Cell::clone(){
  // r: Here are invalid code
  // r: No need to *clone* this object
  // r: Just use copy constructor

  // r: Also compiler warns us
  // r: reference to local variable ‘temp’ returned [-Wreturn-local-addr]
  // r: Cell temp(this->row, this->col);


  // r: Old code
  // Cell temp(this->row, this->col);
  // temp.owner = this->owner;
  // temp.winner = this->winner;

  // r: It's ok to return *this here
  return *this;
}

void Cell::setWinner(int winner){
    this->winner = winner;
}

void Cell::playCell(int newOwner){

    this->owner = newOwner;

    if(!this->owner)
        return;
    if(!this->winner){
        //
    }
}

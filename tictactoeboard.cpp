#include <iostream>

#include "tictactoeboard.h"

TicTacToeBoard::TicTacToeBoard(int row, int col){
    this->row = row;
    this->col = col;
    winner = 0;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cells[i][j] = Cell(i,j);
        }
    }
}

bool TicTacToeBoard::operator!=(const TicTacToeBoard& other){

    if(this->row != other.row)
        return true;
    if(this->col != other.col)
        return true;

    if(this->winner != other.winner)
        return true;

    for(int i=0;i<3; i++){
        for(int j=0; j<3; j++){
            if(cells[i][j] != other.cells[i][j])
                return true;
        }

    }

    return false;
}

TicTacToeBoard::TicTacToeBoard(const TicTacToeBoard& other):
  row(other.row),
  col(other.col),
  winner(other.winner)
{
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      this->cells[i][j] = other.cells[i][j];
    }
  }
}

TicTacToeBoard& TicTacToeBoard::clone(){
    // TicTacToeBoard clone(this->row,this->col);
    // clone.winner = this->winner;
    // for(int ni=0; i<3; i++){
    //     for(int j=0; j<3; j++){
    //         clone.cells[i][j] = this->cells[i][j];
    //     }
    // }

    return *this;
}


bool TicTacToeBoard::isFull(){
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      if(!this->cells[i][j].owner){
        return false;
      }
    }
  }
  return true;
}

std::vector<Cell> TicTacToeBoard::getEmptyCells(){

    std::vector<Cell> emptyCells;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(!this->cells[i][j].owner){
                emptyCells.push_back(this->cells[i][j]);
            }
        }
    }

    return emptyCells;
}

bool TicTacToeBoard::playCellSilently(int row, int col, int player){
    Cell& cell = this->cells[row][col];

    cell.owner = player;
    if(!this->winner){
        bool justWon = this->checkWon(row, col);
        if(justWon){
            //cout << "JustWon!!";
            this->winner = player;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    this->cells[i][j].winner = player;
                }
            }
        }
        return justWon;
    }

    return false;
}

bool TicTacToeBoard::playCell(int row, int col, int player){
    Cell& cell = this->cells[row][col];

    if(!cell.owner){
        cell.playCell(player);

        bool won = false;
        if(!this->winner){
            won = this->checkWon(row, col);
            if(won){
                this->winner = player;
                for(int i=0; i<3; i++){
                    for(int j=0; j<3; j++){
                        this->cells[i][j].setWinner(player);
                    }
                }
            }
        }
        return won;
    } else{
        //Should not get here.
    }

    return false;
}

bool TicTacToeBoard::checkWon(int row, int col){
    int player = this->cells[row][col].owner;

    int i=0;
    while(i<3 &&
          this->cells[row][i].owner &&
          this->cells[row][i].owner == player){
        i += 1;
    }
    if(i == 3){
        return true;
    }

    //check the col
    i=0;
    while(i<3 &&
          this->cells[i][col].owner &&
          this->cells[i][col].owner== player){
        i += 1;
    }
    if(i == 3){
        return true;
    }

    //check the upper left to lower right diagnol
    i=0;
    while(i<3 &&
          this->cells[i][i].owner &&
          this->cells[i][i].owner== player){
        i += 1;
    }
    if(i == 3){
        return true;
    }

    //check the uper right to lower left diagnol
    i=0;
    while(i<3 &&
          this->cells[i][2-i].owner &&
          this->cells[i][2-i].owner == player){
        i += 1;
    }
    if(i == 3){
        return true;
    }
    //None of the rows, cols, or diagnols were winning
    return false;

}

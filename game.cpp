#include "game.h"
#include <QDebug>

Game::Game()
{
    //transit->displayMessage("HELLO");

    currentBoard_valid = 0;
    currentBoard = NULL;
    currentPlayer = -1;
    finished = false;
    winner = 0;
    countFilled = 0;


    for(int row=0; row<3; row++){
        for(int col=0; col<3; col++){

            TicTacToeBoard temp(row,col);
            boards[row][col] = temp;
        }
    }


}


Game::Game(Game &other){

    currentBoard_valid = other.currentBoard_valid;
    currentPlayer = other.currentPlayer;
    finished = other.finished;
    winner = other.winner;
    countFilled = other.countFilled;

    for(int row=0; row<3; row++){
        for(int col=0; col<3; col++){
            boards[row][col] = other.boards[row][col].clone();
        }
    }

    if(other.currentBoard_valid){
        *currentBoard = boards[other.currentBoard->row][other.currentBoard->col];
    }

}

bool Game::checkWonGame(int row, int col, bool silent){

    int player = boards[row][col].winner;

    int i=0;
    while(i<3 && (boards[row][i].winner) && (boards[row][i].winner == player)){
        i += 1;
    }
    if(i == 3){
        return true;
    }

    //check for ultimate win by col
    i=0;
    while(i<3 && (boards[i][col].winner) && (boards[i][col].winner == player)){
        i += 1;
    }
    if(i == 3){
        return true;
    }

    //check for upper left to lower right diagonal
    i=0;
    while(i<3 && (boards[i][i].winner) && (boards[i][i].winner == player)){
        i += 1;
    }
    if(i == 3){
        return true;
    }

    //check for upper right to lower left diagonal
    i=0;
    while(i<3 && (boards[row][2-i].winner) && (boards[row][2-i].winner == player)){
        i += 1;
    }
    if(i == 3)
        return true;


    //None of the rows, cols, diagonals are winning
    return false;
}

void Game::playCellSilently(int board_row, int board_col, int cell_row, int cell_col){

    TicTacToeBoard &board = boards[board_row][board_col];
    //Cell cell = *board.cells[cell_row][cell_col];

    bool justWon = board.playCellSilently(cell_col,cell_col,currentPlayer);

    countFilled += 1;

    if(justWon){
        if(checkWonGame(board_row,board_col,true)){
            finished = true;
            winner = currentPlayer;
            //            qDebug() << "winner: " << currentPlayer;
            //            qDebug() << "game.finished: " << finished;
            return;
        }
    }

    currentBoard = &boards[cell_row][cell_col];
    if(currentBoard->isFull()){
        qDebug() << "currentBoard is full";
        currentBoard = NULL;
    }
    else if(currentBoard->winner && useRule5b){
        currentBoard = NULL;
    }

    //Check for Draws
    if(countFilled == 81){
        finished = true;
    }
    else if(useRule5b && !getNonFinishedBoards().size()){
        finished = true;
        return;
    }

    //X == -1 , O == 1
    if(currentPlayer == -1){
        currentPlayer = 1;
    }
    else{
        currentPlayer = -1;
    }
}



std::vector<TicTacToeBoard> Game::getNonFinishedBoards(){

    std::vector<TicTacToeBoard> nonFinishedBoards;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            TicTacToeBoard board = boards[i][j];
            if(!board.winner && !board.isFull()){
                nonFinishedBoards.push_back(board);
            }
        }
    }
    return nonFinishedBoards;
}

std::vector<Move> Game::getValidMoves(){


    std::vector<TicTacToeBoard> validBoards;

    if(currentBoard_valid){
        validBoards.push_back(*currentBoard);
    }
    else{
        //Choose random Board
        if(useRule5b){
            validBoards = getNonFinishedBoards();
        }
    }


    std::vector<Move> validMoves;
    //qDebug() << "Game::getValidMoves()";
    //qDebug() << "validBoards.size(): " << validBoards.size();

    for(int i=0; i<validBoards.size(); i++){
        TicTacToeBoard board = validBoards[i];
        std::vector<Cell> validCells;
        //This function should return a vector instead. It's much easier to understand.
        board.getEmptyCells(validCells);

        for(int j=0; j<validCells.size(); j++){
            Cell cell = validCells[j];

            Move move(board.row,board.col,cell.row,cell.col);
            validMoves.push_back(move);
        }
    }

    //qDebug() << "Returning from Game::getValidMoves()";

    return validMoves;
}

bool Game::PlayCell(int board_row, int board_col, int cell_row, int cell_col){
    qDebug() << "Game::PlayCell";
    //qDebug() << "CurrentPlayer: " << currentPlayer;
    //qDebug() << "board_row: " << board_row;

    TicTacToeBoard &board = boards[board_row][board_col];

    if(currentBoard && board != *currentBoard){
        qDebug() << "INVALID MOVE";
        return false;
    }

    qDebug() << "Cell_row: " << cell_row;
    qDebug() << "Cell_col: " << cell_col;
    Cell *cell = board.cells[cell_row][cell_col];

    if(cell->owner){
        qDebug() << "OI";
        return false;
    }

    bool justWon = board.playCell(cell_row, cell_col, currentPlayer);

    qDebug() << "test";
    transit->highlight(board_row,board_col,cell_row,cell_col);

    countFilled += 1;
    if(currentBoard_valid){
        //unhighlight. Remove stylesheet
    }

    if(justWon){
        if(checkWonGame(board_row,board_col,true)){
            finished = true;
            winner = currentPlayer;
            //Show winning screen
            return true;
        }
    }

    currentBoard = &boards[cell_row][cell_col];
    if(currentBoard->isFull()){
        currentBoard_valid = 0;
        if(countFilled = 81){
            finished = true;
            //DRAW!!
        }
        else if( currentBoard->winner && useRule5b){
            if(!getNonFinishedBoards().size()){
                finished = true;
                //DRAW!!!
            }
            currentBoard_valid = 0;
        }
        else{
            //highlight currentBoard. Stylesheet
        }
    }
    if(currentPlayer == -1){
        transit->computerMove(board_row,board_col, cell_row, cell_col);
        currentPlayer = 1;

        qDebug() << "CurrentBoard: ";
        qDebug() << "CurrentBoard.row: " << currentBoard->row;
        qDebug() << "CurrentBoard.col: " << currentBoard->col;
    }
    else{
        currentPlayer = -1;
        qDebug() << "CurrentBoard.row: " << currentBoard->row;
        qDebug() << "CurrentBoard.col: " << currentBoard->col;
    }

    qDebug() << "Returning from Game::PlayCell";

}

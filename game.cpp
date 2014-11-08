#include "game.h"

Game::Game()
{

    this->currentPlayer = 1;
    this->currentBoard = nullptr;
    this->finished = false;
    this->winner = 0;
    this->countFilled = 0;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            this->boards[i][j] = new TicTacToeBoard(i,j);
        }
    }
}

Game::Game(const Game& other){
    this->currentPlayer = other.currentPlayer;
    this->finished = other.finished;
    this->winner = other.winner;
    this->countFilled = other.countFilled;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            this->boards[i][j] = new TicTacToeBoard(i,j);
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            //Receiving copy
            *this->boards[i][j] = other.boards[i][j]->clone();
        }
    }

    this->currentBoard = nullptr;

    if(other.currentBoard){
        // currentBoard = new TicTacToeBoard(0,0);

        //this->currentBoard = this->boards[other.currentBoard->row][other.currentBoard->col];
        this->currentBoard = boards[other.currentBoard->row][other.currentBoard->col];
    }
}


void Game::playCellSilently(int board_row, int board_col, int cell_row, int cell_col){

    TicTacToeBoard *board = this->boards[board_row][board_col];
    //Cell cell = *board.cells[cell_row][cell_col];
    bool justWon = board->playCellSilently(cell_row, cell_col, this->currentPlayer);

    this->countFilled += 1;

    if(justWon){
        if(this->checkWonGame(board_row, board_col,true)){
            this->finished = true;
            this->winner = this->currentPlayer;
            return;
        }
    }

    this->currentBoard = this->boards[cell_row][cell_col];

    if(this->currentBoard->isFull()){
        this->currentBoard = nullptr;
    }

    else if(this->currentBoard->winner && useRule5b){
        this->currentBoard = nullptr;
    }

    //check for draws
    if(this->countFilled == 81){
        this->finished = true;
        return;
    }

    else if(useRule5b && !this->getNonFinishedBoards().size()){
        this->finished = true;
        return;
    }

    if(this->currentPlayer == -1){
        this->currentPlayer = 1;
    }
    else{
        this->currentPlayer = -1;
    }
}

bool Game::playCell(int board_row, int board_col, int cell_row, int cell_col){

    TicTacToeBoard *board = this->boards[board_row][board_col];
    if(this->currentBoard && board != this->currentBoard){
        //ERROR WRONG BOARD
        std::cout <<"Assertion: wrong board. Exptected " << this->currentBoard <<  " but got " << board << std::endl;
        //std::exit(1);
        //return;
        return false;
    }

    Cell& cell = board->cells[cell_row][cell_col];

    if(cell.owner){
        std::cout << "Error: Cell already has owner" << std::endl;
        std::exit(1);
        //return;
        return false;
    }

    bool justWon = board->playCell(cell_row,cell_col,this->currentPlayer);

    this->countFilled += 1;
    if(this->currentBoard){
        //unhiglight
    }

    if(justWon){
        qDebug() << "WON BOARD! Player: " << this->currentPlayer;
        transit->wonSlots(board_row, board_col,board->wonSlots);

        if(this->checkWonGame(board_row,board_col,true)){
            this->finished = true;
            this->winner = this->currentPlayer;
            //Show winning screen
            //return;

            //If player == 1
            qDebug() << "Show Winning Screen";
            transit->computerMove(board_row,board_col,cell_row,cell_col);
            return true;
        }
    }

    this->currentBoard = this->boards[cell_row][cell_col];

    if(this->currentBoard->isFull()){
        this->currentBoard = nullptr;
        if(this->countFilled == 81){
            this->finished = true;
            //Show draw screen
        }
    }
    else if(this->currentBoard->winner && useRule5b){
        if(!this->getNonFinishedBoards().size()){
            this->finished = true;
            //show draw screen
        }

        this->currentBoard = nullptr;
    }
    else{
        //this->currentBoard->hightlight;
    }

    if(this->currentPlayer == -1){
        currentPlayer = 1;
        std::cout << "Board Row -1: " << board_row << std::endl;
        std::cout << "Board Col -1: " << board_col << std::endl;
        std::cout << "Cell Row -1: " << cell_row << std::endl;
        std::cout << "Cell Col -1: " << cell_col << std::endl;

    }
    else{
        this->currentPlayer = -1;

        std::cout << "Board Row: " << board_row << std::endl;
        std::cout << "Board Col: " << board_col << std::endl;
        std::cout << "Cell Row: " << cell_row << std::endl;
        std::cout << "Cell Col: " << cell_col << std::endl;
        transit->computerMove(board_row,board_col,cell_row,cell_col);


    }

    return true;
}

std::vector<Move> Game::getValidMoves(){
    std::vector<TicTacToeBoard> validBoards;

    if(this->currentBoard){
        validBoards.push_back(*this->currentBoard);
    }
    else{
        if(useRule5b){
            validBoards = this->getNonFinishedBoards();
        }
    }

    std::vector<Move> validMoves;

    for(unsigned int i=0; i<validBoards.size(); i++){
        TicTacToeBoard board = validBoards[i];
        std::vector<Cell> validCells = board.getEmptyCells();

        for(unsigned int j=0; j<validCells.size();j++){
            Cell cell = validCells[j];
            validMoves.push_back(Move(board.row,board.col,cell.row,cell.col));
        }
    }

    return validMoves;
}

std::vector<TicTacToeBoard> Game::getNonFinishedBoards(){
    std::vector<TicTacToeBoard> nonFinishedBoards;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            TicTacToeBoard board = *this->boards[i][j];
            if(!board.winner && !board.isFull()){
                nonFinishedBoards.push_back(board);
            }
        }
    }

    return nonFinishedBoards;
}

bool Game::checkWonGame(int board_row, int board_col, bool silent){

    /* check if the move at row, col won the board */
    int player = this->boards[board_row][board_col]->winner;
    //check the row
    int i=0;
    while(i<3 &&
          this->boards[board_row][i]->winner &&
          this->boards[board_row][i]->winner== player) {
        i += 1;
    }
    if(i == 3){
        if(!silent) {
            for(i=0; i<3; i++) {
                //this->boards[row][i]->highlight();
            }
        }
        return true;
    }

    //check the col
    i=0;
    while(i<3 &&
          this->boards[i][board_col]->winner &&
          this->boards[i][board_col]->winner == player) {
        i += 1;
    }
    if(i == 3){
        if(!silent) {
            for(i=0; i<3; i++) {
                //this->boards[i][col].highlight();
            }
        }
        return true;
    }

    //check the upper left to lower right diagnol
    i=0;
    while(i<3 &&
          this->boards[i][i]->winner &&
          this->boards[i][i]->winner == player) {
        i += 1;
    }
    if(i == 3){
        if(!silent) {
            for(i=0; i<3; i++) {
                //this.boards[i][i].highlight();
            }
        }
        return true;
    }

    //check the uper right to lower left diagnol
    i=0;
    while(i<3 &&
          this->boards[i][2-i]->winner &&
          this->boards[i][2-i]->winner == player) {
        i += 1;
    }
    if(i == 3){
        if(!silent) {
            for(i=0; i<3; i++) {
                //this.boards[i][2-i].highlight();
            }
        }
        return true;
    }
    //None of the rows, cols, or diagnols were winning
    return false;
}


std::string Game::getBoardDraw() const {

    std::string result;

    for(int br=0; br < 3; br++){ // Iterating board rows
        for(int cr=0; cr < 3; cr++){ // Iterating col rows
            for(int bc=0; bc < 3; bc++){ // Iterating board columns
                for(int cc=0; cc < 3; cc++){ // Iterating col columns
                    std::string out("-");

                    if(this->boards[br][bc]->winner > 0){
                        result.append("\033[1;31m");
                    }
                    else if(this->boards[br][bc]->winner < 0) {
                        result.append("\033[1;32m");
                    }
                    else{
                        result.append("\033[0m");
                    }

                    Cell cell = this->boards[br][bc]->cells[cr][cc];
                    if(cell.owner){

                        out = cell.owner > 0 ? "X" : "O";
                    }
                    result.append(out);
                }
                result.append(" ");
            }
            result.append("\n");
        }
        result.append("\n");
    }
    result.append("\033[0m");
    return result;
}

#include "tictactoe.h"

#include <QTextStream>
#include <QProcess>
#include <stdio.h>
#include <QDebug>

using std::cout;
using std::endl;


TicTacToe::TicTacToe(QObject *parent) : QObject(parent)
{

    std::fill(boards.begin(),boards.end(),std::vector<int>(NUM_SQUARES,EMPTY));

}

int TicTacToe::opponent(int piece){
    if(piece == -1)
        return 1;
    else
        return -1;
}

void TicTacToe::humanMove(int move,int currentGrid){

    boards[currentGrid][move] = human;

}


bool TicTacToe::isLegal(int move,int currentGrid) const{
    qDebug() << "[0][0] << " << boards[0][4];
    qDebug() << "wut: " << boards[currentGrid][move] << endl;
    return (boards[currentGrid][move] == EMPTY);
}

int TicTacToe::winner(const std::vector<int> &board){

    const int WINNING_ROWS[8][3] = {
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6} };
    const int TOTAL_ROWS = 8;

    for(int row = 0; row < TOTAL_ROWS; ++row){

        if( (board[WINNING_ROWS[row][0]] != EMPTY) &&                              //Go through the rows of WINNING_ROWS and determine if board[x][y] is winner
                (board[WINNING_ROWS[row][0]] == (board[WINNING_ROWS[row][1]])) &&
                (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]) )
        {
            return board[WINNING_ROWS[row][0]]; //Return the character that has won
        }
    }

    //No one has won yet
    return 0;
}

int TicTacToe::winner(int currentGrid){

    qDebug() << "Checking winner at " << currentGrid;

    const int WINNING_ROWS[8][3] = {
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6} };
    const int TOTAL_ROWS = 8;

    for(int row = 0; row < TOTAL_ROWS; ++row){

        if( (boards[currentGrid][WINNING_ROWS[row][0]] != EMPTY) &&                              //Go through the rows of WINNING_ROWS and determine if board[x][y] is winner
                (boards[currentGrid][WINNING_ROWS[row][0]] == boards[currentGrid][WINNING_ROWS[row][1]]) &&
                (boards[currentGrid][WINNING_ROWS[row][1]] == boards[currentGrid][WINNING_ROWS[row][2]]) )
        {
            return boards[currentGrid][WINNING_ROWS[row][0]]; //Return the character that has won
        }
    }

    //Check for tie. If no more empty spots, no more moves
    if(count(boards[currentGrid].begin(), boards[currentGrid].end(), EMPTY) == 0)
        return 0;
}

void TicTacToe::reset(){
    board = std::vector<int>(NUM_SQUARES,EMPTY);
}

int TicTacToe::minimax(std::vector<int>& board, int player){
    //printf("Entered minimax. player: %d\n", player);
    //qDebug() << "Entered minimax. player: " << player << endl;

    //How is the position like for player (their turn) on board?
    int win = winner(board);
    if(win != 0)
    {
        return win*player;
    }

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == EMPTY) {//If legal,
            board[i] = player;//Try the move

            int thisScore = -minimax(board, player*-1);
            //printf("thisScore: %d, score: %d, player: %d\n",thisScore,score,player);
            //qDebug() << "player*-1: " << player *-1 << endl;
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try

        }
    }

    if(move == -1) return 0;
    return score;

}

void TicTacToe::computerMax(){
    //qDebug() << "Inside computerMax()\n";
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(boards[0][i] == EMPTY) {
            boards[0][i] = 1;
            int tempScore = -minimax(boards[0], -1);
            boards[0][i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    boards[0][move] = 1;

    qDebug() << "before emit: " << move << endl;

    emit computerMove(move,0); //ambiguous

}

char TicTacToe::gridChar(int i) {
    switch(i) {
    case -1:
        return 'X';
    case 0:
        return ' ';
    case 1:
        return 'O';
    }

    return 0;
}



//Ultimate Tic-Tac-Toe Functionality

int TicTacToe::CalculateGrid(int currentGrid){

    qDebug() << "CurrentGrid: " << currentGrid << endl;

    int move = -1;
    int score = -2;
    int i;

    if(gridStates[currentGrid] == EMPTY){
        for(i = 0; i < 9; ++i) {
            if(boards[currentGrid][i] == EMPTY && gridStates[i] == EMPTY) {
                qDebug() << "in loop";
                boards[currentGrid][i] = 1;
                int tempScore = -minimax(boards[i], -1);
                boards[currentGrid][i] = 0;
                if(tempScore > score) {
                    score = tempScore;
                    move = i;
                }
            }
        }
        boards[currentGrid][move] = 1;
        emit computerMove(move,currentGrid); //ambiguous
        return 0;


    }

        int movement;
        for(int j=0; j<9; ++j){
        for(i = 0; i < 9; ++i) {
            if(boards[j][i] == EMPTY && gridStates[j] == EMPTY) {
                qDebug() << "J in loop: " << j;
                boards[j][i] = 1;
                int tempScore = -minimax(boards[i], -1);
                boards[j][i] = 0;
                if(tempScore > score && gridStates[i] == EMPTY) {
                    score = tempScore;
                    move = i;
                    movement = j;
                }
            }
        }
    }
        qDebug() << "movement: " << movement;
        qDebug() << "move_: " << move;
        boards[movement][move] = 1;
        emit computerMove(move,movement); //ambiguous



    //returns a score based on minimax tree at a given node.
    //boards[currentGrid][move] = 1;

    qDebug() << "before emit: " << move << endl;

    //emit computerMove(move); //ambiguous


}
//Calculates which tile to play

void TicTacToe::setGridState(int grid, int winner){

    gridStates[grid] = winner;
}


int TicTacToe::ultWin(){

    return winner(gridStates);
}

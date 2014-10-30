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

void TicTacToe::humanMove(int move,int currentGrid){

    boards[currentGrid][move] = human;

}


bool TicTacToe::isLegal(int move,int currentGrid) const{

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
            winningRows[0] = WINNING_ROWS[row][0];
            winningRows[1] = WINNING_ROWS[row][1];
            winningRows[2] = WINNING_ROWS[row][2];
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
//Calculates which tile to play

int TicTacToe::CalculateGrid(int currentGrid){

    //If a player forces the computer to a score that has already been won...welp.
    //Computer gets to pick whichever grid he wants. 2 guud 4 uuu
    int test;
    if(gridStates[currentGrid] != EMPTY){
        qDebug() << "NOT EMPTY" << endl << endl;
        int move,best,bestscore = -20000;
        for(int i=0; i<9; i++){
            qDebug() << "looping";
            if((i != currentGrid)){
                move = pickMove(i,best);
                qDebug() << "best: " << best;
                if(best > bestscore && boards[move][i] == EMPTY){
                    qDebug() << "move: " << move << " i: " << i;
                    boards[move][i] = 1;
                    emit computerMove(move,i);
                    return 20;
                }
            }
        }
    }


    int movetomake = pickMove(currentGrid,test);

    boards[currentGrid][movetomake] = 1;
    emit computerMove(movetomake,currentGrid);
    return 20;
}


void TicTacToe::setGridState(int grid, int winner){

    gridStates[grid] = winner;
}


int TicTacToe::ultWin(){

    return winner(gridStates);
}

void TicTacToe::utility(int currentGrid,int move,int depth){


    bool win = false;

    int triad_sum = 0;
    int score = 0;


    int numElements = BY_SLOT[move][0];

    for(int i=1; i<=numElements; i++){
        triad_sum = 0;
        for(int j=0; j<3; j++){
            triad_sum += boards[currentGrid][WINNING_TRIADS[BY_SLOT[move][i]][j]];
        }



        switch(triad_sum){

        case 3:
        case -3:
        {
            win = 1;
            score = boards[currentGrid][WINNING_TRIADS[BY_SLOT[move][i]][0]] * VERY_LARGE - depth;
            break;
        }
        case 2:{
            score += 3000;
            break;
        }
        case -2:
            score -=3000;
            break;
        case 1:
        case -1:{
            if((boards[currentGrid][WINNING_TRIADS[BY_SLOT[move][i]][0]] & boards[currentGrid][WINNING_TRIADS[BY_SLOT[move][i]][1]] & boards[currentGrid][WINNING_TRIADS[BY_SLOT[move][i]][2]]) != 0){
                score -= triad_sum * 1000;
            }
            break;
        }
        case 0:{
            score += boards[currentGrid][move];
            break;
        }
        default:
            break;
        }

        if(win){
            break;
        }


    }


    if(!win){

        //qDebug() << "BScore: " << score;
        int bonus = 0;
        if(move == 0 || move == 2 || move == 6 || move == 8){
            bonus += 2;//*boards[currentGrid][move];
        }
        if(move == 4){
            bonus += 7;//*boards[currentGrid][move];
        }
        //qDebug() << "boards[currentGrid][move]: " << boards[currentGrid][move];
        //qDebug() << "bonus: " << bonus;
        //        qDebug() << "Bonus: " << bonus;
        //        qDebug() << "Slot: " << move;
        //        qDebug() << "Move: " << currentGrid;
        //        qDebug() << "board[move]: " << boards[currentGrid][move];

        score += boards[currentGrid][move]*bonus;


    }


    rets[0] = score;
    rets[1] = win;

}

int TicTacToe::pickMove(int currentGrid,int& best){

    int score = 0;
    int bestScore = -VERY_LARGE - DEPTH_LIMIT;
    std::vector<int> my_moves;


    for(int slot=0; slot<9; slot++){

        if(boards[currentGrid][slot] == EMPTY){
            boards[currentGrid][slot] = 1;


            utility(currentGrid,slot,0);
            score = alphaBeta(boards[currentGrid],slot,-1,1,(-(VERY_LARGE+DEPTH_LIMIT)-1),(VERY_LARGE+DEPTH_LIMIT+1),1,rets[0],rets[1]);

            boards[currentGrid][slot] = 0;

            if(score > bestScore){
                bestScore = score;
                my_moves.push_back(slot);
            }
            else if(score == bestScore){
                //my_moves.push_back(i);
            }


        }

        qDebug() << "Move: " << slot << " Score: " << score;



    }

    int rv = 0;
    if(my_moves.size() < 1){

    }
    else{
        rv = my_moves.back();


    }


    qDebug() << "Ultimate move: " << rv << endl;
    qDebug() << "score: " << score;
    best = score;
    return rv;

}

int TicTacToe::alphaBeta(std::vector<int>& board,int last_slot,int player, int next_player,int alpha, int beta, int depth, int score_so_far, int last_move_won){



    if(last_move_won || depth >= DEPTH_LIMIT){
        return score_so_far;
    }



    int score = score_so_far;
    int value;

    for(int i=0; i<9; i++){
        if(boards[last_slot][i] == EMPTY){
            boards[last_slot][i] = player;

            utility(last_slot,i,depth);
            value = alphaBeta(board,i,next_player,player,alpha,beta,depth+1,score_so_far + rets[0],rets[1]);

            boards[last_slot][i] = 0;

            switch(player){
            case 1:
                if(value > alpha)
                    alpha = value;
                break;
            case -1:
                if(value < beta)
                    beta = value;
                break;
            }
            if(beta <= alpha)
                break;
        }

    }

    score = beta;
    if(player == 1)
        score = alpha;


    return score;

}

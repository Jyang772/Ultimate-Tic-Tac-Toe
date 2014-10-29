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
        return win*player*2;
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

    //qDebug() << "TEST FUNCTION RESULTS: " << pickMove(currentGrid) << endl;

    //qDebug() << "CurrentGrid: " << currentGrid << endl;

    int movetomake = pickMove(currentGrid);

    boards[currentGrid][movetomake] = 1;
    emit computerMove(movetomake,currentGrid);
    return 20;


//    qDebug() << "UTILITY: ";
//    boards[currentGrid][1] = 1;
//    utility(currentGrid,1,1);
//    boards[currentGrid][1] = 0;

    //utility(currentGrid,0);

    int move = -1;
    int score = -2;
    int score2 = -2;
    int i;

    if(gridStates[currentGrid] == EMPTY){
        for(i = 0; i < 9; ++i) {
            if(boards[currentGrid][i] == EMPTY && gridStates[i] == EMPTY) {

                boards[currentGrid][i] = 1;
                int tempScore = -minimax(boards[i], -1);             //Test for possible moves for other subBoards
                int tempScore2 = -minimax(boards[currentGrid],-1);   //Test to see how possible moves affect currentGrid
                boards[currentGrid][i] = 0;
                qDebug() << "tempScore2: " << tempScore2 << " i: " << i;
                qDebug() << "score: " << score << " i: " << i;
                qDebug() << "score2: " << score2 << " i: " << i;
                if(tempScore > score) {
                    qDebug() << "tempScore: " << tempScore;
                    qDebug() << "tempScore2: " << tempScore2;
                    score = tempScore;

                    move = i;
                }
                if(tempScore2 > score || tempScore2 > score2 ){
                    move = i;
                    score2 = tempScore2;

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

void TicTacToe::utility(int currentGrid,int move,int depth){

    bool win = false;

    int triad_sum = 0;
    int score = 0;



    //for(int i=0; i<9; i++){


    int temp = 0;
    for(int j=0; j<8; j++){
        temp = 0;
        //if(boards[currentGrid][move] == EMPTY){
            //boards[currentGrid][move] = 1;

            temp = boards[currentGrid][WINNING_TRIADS[j][0]] + boards[currentGrid][WINNING_TRIADS[j][1]] + boards[currentGrid][WINNING_TRIADS[j][2]];
            triad_sum = temp;
            //                if(temp > triad_sum){
            //                    triad_sum = temp;
            //                    index = i;
            //                    qDebug() << "Score_: " << score;
            //                    qDebug() << "triad_sum: " << triad_sum;
            //                }
            //boards[currentGrid][move] = EMPTY;
        //}


        qDebug() << "TRIAD_SUM: " << triad_sum << " i: " << currentGrid << " j: " << move << endl;
        switch(triad_sum){

        case 3:
        case -3:
            win = true;
            score = boards[currentGrid][move] * VERY_LARGE - depth;
            break;
        case 2:{
            score += 3000;
            qDebug() << "THIS IS THE MOVE TO MAKE: " << move;
            break;
        }
        case -2:
            score -=3000;
            break;
        case 1:
        case -1:{
            if((boards[currentGrid][WINNING_TRIADS[j][0]] & boards[currentGrid][WINNING_TRIADS[j][1]] & boards[currentGrid][WINNING_TRIADS[j][2]]) != 0){
                score -= triad_sum * 1000;}
            break;
        }
        case 0:
            score += boards[currentGrid][move];
        default:
            break;
        }

        if(win){
            rets[0] = score;
            rets[1] = win;
            break;
        }

        qDebug() << "Score progress: " << score;
    }

    if(!win){

        qDebug() << "DID NOT WIN: " << move << endl;

        if(move == 0 || move == 2 || move == 6 || move == 8)
            score += 2;
        else if(move == 4)
            score += 7;


    }

    qDebug() << "FIRST DIG";


    rets[0] = score;
    rets[1] = win;

}





int TicTacToe::pickMove(int currentGrid){

    int score = 0;
    int bestScore = -VERY_LARGE - DEPTH_LIMIT;
    std::vector<int> my_moves;

    //int bestScore = -VERY_LARGE - DEPTH_LIMIT;

    qDebug() << "BEST SCORE: " << bestScore;

    for(int i=0; i<9; i++){

        if(boards[currentGrid][i] == EMPTY){
            boards[currentGrid][i] = 1;


            utility(currentGrid,i,0);

            qDebug() << "RETS[0]: " << rets[0];

            score = alphaBeta(boards[currentGrid],currentGrid,1,-1,(-(VERY_LARGE+DEPTH_LIMIT)-1),(VERY_LARGE+DEPTH_LIMIT+1),2,rets[0],rets[1]);
            qDebug() << "SCORE: " << score << " i: " << i << endl;

            boards[currentGrid][i] = 0;

            qDebug() << "DONE: " << i;


            if(score > bestScore){
                bestScore = score;
                my_moves.push_back(i);
            }
            else if(score == bestScore){
                my_moves.push_back(i);
            }


        }


    }

    int rv = 0;
    if(my_moves.size() < 1)
        qDebug() << "ERROR.";
    else{
        rv = my_moves[0];
        if(my_moves.size() > 1){
            //Choose a move at random.
        }

    }


    qDebug() << "COMPUTER MOVE: " << rv << endl;
    return rv;

}




int TicTacToe::alphaBeta(std::vector<int>& board,int last_slot,int player, int next_player,int alpha, int beta, int depth, int score_so_far, int last_move_won){

    if(last_move_won || depth >= DEPTH_LIMIT){
        return score_so_far;
    }

    int score = score_so_far;
    int value;

    for(int i=0; i<9; i++){
        if(board[i] == EMPTY){
            board[i] = player;

            utility(last_slot,i,depth);
            value = alphaBeta(board,i,next_player,player,alpha,beta,depth+1,score_so_far + rets[0],rets[1]);

            board[i] = 0;

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

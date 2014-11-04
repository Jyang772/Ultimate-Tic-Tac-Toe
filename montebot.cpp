#include "montebot.h"
#include <QDebug>

MonteBot::MonteBot()
{
}


void MonteBot::StartCalculation(Game &game){
    Move move;

    //qDebug() << "Starting calculations";
    //qDebug() << "game.currentBoard_valid: " << game.currentBoard_valid;
    std::vector<Move> validMoves = game.getValidMoves();
    //qDebug() << "Withing";

    Game *clone;

    endThinkTime = /*Time passed*/ + botThinkingTime;

    for(int i=0; i<validMoves.size(); i++){
        move = validMoves[i];
        clone = new Game(game);
        clone->playCellSilently(move.bRow,move.bCol,move.cRow,move.cCol);

        Clone clone_;

        clone_.boardRow = move.bRow;
        clone_.boardCol = move.bCol;
        clone_.cellRow = move.cRow;
        clone_.cellCol = move.cCol;
        clone_.clone = *clone;
        clone_.wins = 0;
        clone_.weightedWins = 0;
        clone_.losses = 0;
        clone_.weightedLosses = 0;
        clone_.ties = 0;

       clones.push_back(clone_);
    }

}


void MonteBot::CalculateAhead(Game &game){

    randomBot random;

    for(int i=0; i<clones.size(); i++){
        Clone &move = clones[i];

        Game *simGame = new Game(move.clone);

        int winner = random.playOutHidden(*simGame);
        double weight = 1;

        if(monteWeightByGameLength){
            double f = simGame->countFilled - game.countFilled;
            double r = 81 - game.countFilled;


            weight = (r-f)/r;
            qDebug() << "Weight: " << weight;

        }

        if(winner == 0){
            move.ties += 1;
        }
        else{
            if(winner == game.currentPlayer){
                move.wins += 1;
                move.weightedWins += 1*weight;
            }
            else{
                move.losses += 1;
                move.weightedLosses += 1*weight;
            }
        }
    }


}

void MonteBot::Play(Game &game){


    int bestScore = -10000;
    Clone bestMove;

    for(int i=0; i<clones.size(); i++){
        int penalty = 1;
        Clone &clone = clones[i];


        if(!clone.clone.currentBoard){
            penalty = monteChoicePenalty;
        }

//        qDebug() << "clone.weightedWins: " << clone.weightedWins;
//        qDebug() << "clone.weightedLosses: " << clone.weightedLosses;
//        qDebug() << "clone.wins: " << clone.wins;
//        qDebug() << "clone.losses: " << clone.losses;
//        qDebug() << "clone.ties: " << clone.ties;

        double score = (clone.weightedWins - clone.weightedLosses*penalty) / (clone.wins + clone.losses + clone.ties);

        if(score > bestScore){
            bestScore = score;
            bestMove = clone;
        }

    }

    qDebug() << "board_row: " << bestMove.boardRow;
    qDebug() << "board_col: " << bestMove.boardCol;
    qDebug() << "cell_row: " << bestMove.cellRow;
    qDebug() << "cell_col: " << bestMove.cellCol;

        //Play Cell at bestMove.boardRow , etc.
    game.PlayCell(bestMove.boardRow,bestMove.boardCol,bestMove.cellRow,bestMove.cellCol);
}

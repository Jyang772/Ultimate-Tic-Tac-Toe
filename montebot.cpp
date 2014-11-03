#include "montebot.h"

MonteBot::MonteBot()
{
}


void MonteBot::StartCalculation(Game game){
    Move move;
    std::vector<Move> validMoves = game.getValidMoves();

    Game clone;

    endThinkTime = /*Time passed*/ + botThinkingTime;

    for(int i=0; i<validMoves.size(); i++){
        move = validMoves[i];
        clone.playCellSilently(move.bRow,move.bCol,move.cRow,move.cCol);

        Clone clone_;

        clone_.boardRow = move.bRow;
        clone_.boardCol = move.bCol;
        clone_.cellRow = move.cRow;
        clone_.cellCol = move.cCol;
        clone_.clone = clone;
        clone_.wins = 0;
        clone_.weightedWins = 0;
        clone_.losses = 0;
        clone_.weightedLosses = 0;
        clone_.ties = 0;

        clones.push_back(clone_);
    }

}


void MonteBot::CalculateAhead(Game game){

    randomBot random;

    for(int i=0; i<clones.size(); i++){
        Clone move = clones[i];
        Game simGame = Game(move.clone);

        int winner = random.playOutHidden(simGame);
        int weight = 1;

        if(monteWeightByGameLength){
            int f = simGame.countFilled - game.countFilled;
            int r = 81 - game.countFilled;

            weight = (r-f)/r;
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

void MonteBot::Play(Game game){

    int bestScore = -10000;
    Clone bestMove;

    for(int i=0; i<clones.size(); i++){
        int penalty = 1;
        Clone clone = clones[i];

        if(!clone.clone.currentBoard_valid){
            penalty = monteChoicePenalty;
        }
        int score = (clone.weightedWins - clone.weightedLosses*penalty) / (clone.wins + clone.losses + clone.ties);

        if(score > bestScore){
            bestScore = score;
            bestMove = clone;
        }
    }

    //Play Cell at bestMove.boardRow , etc.
}

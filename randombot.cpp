#include "randombot.h"
#include <ctime>

randomBot::randomBot()
{
    std::srand(time_t());
}


Move randomBot::getRandomValidMove(Game &game){

    std::vector<Move> moves = game.getValidMoves();

    //select one move at random.
    int moveNum = std::rand() % moves.size();

    return moves[moveNum];
}

int randomBot::playOutHidden(Game &game){

    while(!game.finished){

        Move move = getRandomValidMove(game);
        game.playCellSilently(move.bRow,move.bCol,move.cRow,move.cCol);
    }
    return game.winner;
}

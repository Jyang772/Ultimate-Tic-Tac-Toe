#include "randombot.h"
#include <ctime>
#include <QDebug>

randomBot::randomBot()
{
    std::srand(time(NULL));
}


Move randomBot::getRandomValidMove(Game &game){

    std::vector<Move> moves = game.getValidMoves();

    //select one move at random.
    int moveNum = std::rand() % moves.size();


//    qDebug() << moves[moveNum].bRow;
//    qDebug() << moves[moveNum].bCol;
//    qDebug() << moves[moveNum].cRow;
//    qDebug() << moves[moveNum].cCol;

    return moves[moveNum];
}

int randomBot::playOutHidden(Game &game){

    while(!game.finished){

        Move move = getRandomValidMove(game);
        game.playCellSilently(move.bRow,move.bCol,move.cRow,move.cCol);
    }


    return game.winner;
}

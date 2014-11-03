#ifndef RANDOMBOT_H
#define RANDOMBOT_H

#include "game.h"
#include "move.h"

class randomBot
{
public:
    randomBot();

    Move getRandomValidMove(Game &);

    int playOutHidden(Game &);
};

#endif // RANDOMBOT_H

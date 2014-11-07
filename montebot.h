#ifndef MONTEBOT_H
#define MONTEBOT_H

#include "game.h"
#include "clone.h"

#include <iostream>

class MonteBot{
public:
    void startCalculation(Game&);
    void calculateAhead(Game&);
    void play(Game&);
    int playOutHidden(Game&);
    Move getRandomValidMove(Game &);

    std::vector<Clone> clones;

    bool monteWeightByGameLength = true;

    int botThinkingTime;
};

#endif // MONTEBOT_H

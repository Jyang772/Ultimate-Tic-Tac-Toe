#ifndef MONTEBOT_H
#define MONTEBOT_H

#include "move.h"
#include "cell.h"
#include "board.h"
#include "tictactoeboard.h"
#include "game.h"
#include "randombot.h"


struct Clone{
    int boardRow;
    int boardCol;
    int cellRow;
    int cellCol;
    Game clone;
    int wins;
    int weightedWins;
    int losses;
    int weightedLosses;
    int ties;
};

class MonteBot
{
public:
    MonteBot();
    void Play(Game);
    void StartCalculation(Game);
    void CalculateAhead(Game);


    int endThinkTime;
    int botThinkingTime;
    int monteChoicePenalty = 10;
    bool monteWeightByGameLength = true;


    Game *clone;
    std::vector<Clone> clones;

};

#endif // MONTEBOT_H

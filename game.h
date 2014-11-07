#ifndef GAME_H
#define GAME_H

#include "move.h"
#include "tictactoeboard.h"
#include "transmitter.h"


#include <vector>
#include <iostream>

class Game{
public:
    Game();
    Game(const Game& other);

    void playCellSilently(int board_row, int board_col, int cell_row, int cell_col);
    bool playCell(int board_row, int board_col, int cell_row, int cell_col);

    std::vector<Move> getValidMoves();
    std::vector<TicTacToeBoard> getNonFinishedBoards();
    bool checkWonGame(int board_row, int board_col, bool silent);


    std::string getBoardDraw() const;

    int currentPlayer;
    bool finished;
    int winner = 0;
    int countFilled;
    bool useRule5b = true;
    TicTacToeBoard *currentBoard; //Pointer to currentBoard
    TicTacToeBoard *boards[3][3];

    Transmitter *transit = new Transmitter;


};



#endif // GAME_H

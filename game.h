#ifndef GAME_H
#define GAME_H

#include "move.h"
#include "cell.h"
#include "tictactoeboard.h"
#include "transmitter.h"
#include <vector>
#include <array>


class Game
{
public:
    Game();
    Game(Game&);
    void playCellSilently(int board_row,int board_col,int cell_row,int cell_col);
    bool checkWonGame(int row, int col, bool silent);
    std::vector<TicTacToeBoard> getNonFinishedBoards();
    std::vector<Move> getValidMoves();

    bool PlayCell(int board_row, int board_col, int cell_row, int cell_col);


    bool useRule5b = true;
    int currentPlayer = -1;
    TicTacToeBoard *currentBoard;
    bool finished = false;
    int winner = 0;
    int countFilled = 0;

    //For setting currentboard to null.
    int currentBoard_valid;

    //std::array<std::vector<TicTacToeBoard>,3> boards;
    TicTacToeBoard boards[3][3];


    Transmitter *transit = new Transmitter();

};

#endif // GAME_H

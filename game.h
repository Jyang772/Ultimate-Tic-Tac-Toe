#ifndef GAME_H
#define GAME_H

#include "move.h"
#include "cell.h"
#include "board.h"
#include "tictactoeboard.h"

#include <vector>
#include <array>
#include <QObject>


class Game : public QObject
{

    Q_OBJECT

public:
    Game();
    void playCellSilently(int board_row,int board_col,int cell_row,int cell_col);
    bool checkWonGame(int row, int col, bool silent);
    std::vector<TicTacToeBoard> getNonFinishedBoards();
    std::vector<Move> getValidMoves();

    void PlayCell(int board_row, int board_col, int cell_row, int cell_col);


    bool useRule5b = true;
    int currentPlayer = -1;
    TicTacToeBoard currentBoard;
    bool finished = false;
    int winner = -99;
    int countFilled = 0;

    //For setting currentboard to null.
    int currentBoard_valid = 1;

    std::array<std::vector<TicTacToeBoard>,9> boards;

};

#endif // GAME_H

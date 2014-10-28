#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <vector>
#include <QObject>

//global constants
const int NUM_SQUARES = 9;
const char X = 'X';
const char O = 'O';
//const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';
const int EMPTY = 0;


const int WINNING_TRIADS[8][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6},
};


class TicTacToe : public QObject
{
    Q_OBJECT

public:
    explicit TicTacToe(QObject *parent = 0);

    int winner(const std::vector<int>& board); //Checks to see if anyone has won
    int winner(int currentGrid);

    int opponent(int piece);
    bool isLegal(int move, int currentGrid) const;

    int human;
    int turn;

    void reset();

    //Minimax
    void computerMax();
    int minimax(std::vector<int>& board,int player);
    char gridChar(int i);

    //Ultimate
    int CalculateGrid(int currentGrid);
    void setGridState(int grid, int winner);
    int ultWin();

    int utility(int);

signals:
    void humanMoves();
    void computerMove(int,int);

public slots:
    void humanMove(int,int currentGrid);

private:
    //Compiler derps with initialization of aggregate members
    //std::vector<char> board{std::vector<char>(NUM_SQUARES,EMPTY)};
    std::vector<int> board = std::vector<int>(NUM_SQUARES,EMPTY);
    std::vector<int> gridStates = std::vector<int>(NUM_SQUARES,EMPTY);                            //Keep track of Grids that have been completed. Stores either 0,-1,1

    std::array<std::vector<int>,9> boards;        //Array that contains all boards from each Grid
};

#endif // TICTACTOE_H

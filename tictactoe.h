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

//int DEPTH_LIMIT = 2;
const int VERY_LARGE = 2000000;



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


const int BY_SLOT[9][5] = {

    {3,0,3,6},  //First element tells how many elements are present
    {2,0,4},
    {3,0,5,7},
    {2,1,3},
    {4,1,4,6,7},
    {2,1,5},
    {3,2,3,7},
    {2,2,4},
    {3,2,5,6}
};

class TicTacToe : public QObject
{
    Q_OBJECT

public:
    explicit TicTacToe(QObject *parent = 0);

    int DEPTH_LIMIT = 2;


    int human = -1;
    int turn;
    int winningRows[3];


    void setDepth(int strength);

    bool isLegal(int move, int currentGrid) const;

    void reset();

    //Minimax
    char gridChar(int i);

    //Ultimate
    int CalculateGrid(int currentGrid);
    void setGridState(int grid, int winner);
    int ultWin();

    //Check for winners
    int winner(const std::vector<int>& board); //Checks to see if anyone has won
    int winner(int currentGrid);


    //Fundamental Ultimate Tic-Tac-Toe
    int pickMove(int,int&);
    void utility(int,int,int);
    int alphaBeta(std::vector<int>& board,int last_slot,int player, int next_player,int alpha, int beta, int depth, int score_so_far, int last_move_won);


signals:
    void humanMoves();
    void computerMove(int,int);

public slots:
    void humanMove(int,int currentGrid);

private:
    //Compiler derps with initialization of aggregate members
    //std::vector<char> board{std::vector<char>(NUM_SQUARES,EMPTY)};


    int wonGrids[9] = {};
    std::vector<int> board = std::vector<int>(NUM_SQUARES,EMPTY);
    std::vector<int> gridStates = std::vector<int>(NUM_SQUARES,EMPTY);                            //Keep track of Grids that have been completed. Stores either 0,-1,1

    std::array<std::vector<int>,9> boards;        //Array that contains all boards from each Grid

    int rets[2] = {};

};

#endif // TICTACTOE_H

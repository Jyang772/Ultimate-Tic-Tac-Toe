#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include "tictactoe.h"
#include "montebot.h"
#include "move.h";
#include "game.h"
#include "transmitter.h"

#include <string.h>
#include <iostream>
#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QThread>
#include <QtConcurrent>
#include <QFuture>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int player = 1; //Keeps track of current

    explicit MainWindow(QWidget *parent = 0);
    void setUpGrid();
    void setChar(char);
    void Play();
    void CheckWinner(int currentGrid);

    void colorBoard(int nextGrid, int move);
    void colorBoardWin(int nextGrid,int player);
    void colorBoardUltimateWin(int player);

    void computer(int grid, int player);
    ~MainWindow();


    //MonteCarlo
    void computerMoves();

signals:
    void turnComplete(int);
    void computer_(int,int player);

public slots:
    int itemClicked();
    void humanMoves();

    //void computer(int grid,int player);
    void prediction(QString);


    //For MonteBot
    void wonBoard(int,int,int);

private slots:

    void begin(int strength,bool mode);
    void invalidMove();
    void on_playAgain_clicked();

    //For winbyone
    void computerMove(int slot,int grid);


    //For MonteBot
    void computerMove(int board_row, int board_col, int cell_row, int cell_col);
    void wonSlots(int board_row, int board_col, std::vector<Move>&);




private:
    Ui::MainWindow *ui;
    Dialog *options = new Dialog;

    QPushButton *itemButtons[9][9];
    QGridLayout *layouts[9];
    QFrame *frames[9];



    QPushButton *createButton(QString&, const QString/*const char**/);

    TicTacToe *game = new TicTacToe();

    int strength;
    bool humanTurn;

    int currentGrid = -1;
    int nextGrid = -1;


    int wonGrids[9] = {};
    int previousMove[2] = {-1,-1};  //Stores currentGrid, move


    int test = -1;


    QThread *pthread = new QThread();

    MonteBot montebot;
    Game newgame;
    Transmitter *transit = new Transmitter();
    bool mode = false;

};

#endif // MAINWINDOW_H

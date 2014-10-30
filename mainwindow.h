#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include "tictactoe.h"
#include <string.h>
#include <iostream>
#include <QMainWindow>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setUpGrid();
    void setChar(char);
    void Play();
    void CheckWinner();

    void colorBoard(int nextGrid, int move);
    void colorBoardWin(int nextGrid,int player);
    void colorBoardUltimateWin(int player);

    ~MainWindow();

signals:
    void turnComplete(int);

private slots:
    void itemClicked();
    void begin(int strength);

    void humanMoves();
    void invalidMove();
    void computerMove(int,int);


    void on_playAgain_clicked();

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
    int player; //Keeps track of current player



};

#endif // MAINWINDOW_H

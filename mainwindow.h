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

    ~MainWindow();

signals:
    void turnComplete(int);

private slots:
    void itemClicked();
    void begin();

    void humanMoves();
    void invalidMove();
    void computerMove(int,int);


    void on_playAgain_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *options = new Dialog;

    QPushButton *itemButtons[9][9];
    QGridLayout *layouts[9];

    QPushButton *createButton(QString&, const QString/*const char**/);

    TicTacToe *game = new TicTacToe();

    bool humanTurn;

    int currentGrid = 0;
    int nextGrid = 0;

};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    humanTurn = false;

    ui->playAgain->setVisible(false);

    options->setWindowFlags(Qt::WindowStaysOnTopHint);
    options->setModal(true);
    options->show();

    setUpGrid();


    connect(options,SIGNAL(choosen()),this,SLOT(begin()));
    connect(game,SIGNAL(humanMoves()),this,SLOT(humanMoves()));
    connect(game,SIGNAL(computerMove(int,int)),this,SLOT(computerMove(int,int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpGrid(){




    layouts[0] = ui->gridLayout;
    layouts[0]->parent()->setObjectName(QString::number(0));
    layouts[1] = ui->gridLayout_2;
    layouts[1]->parent()->setObjectName(QString::number(1));
    layouts[2] = ui->gridLayout_3;
    layouts[2]->parent()->setObjectName(QString::number(2));
    layouts[3] = ui->gridLayout_4;
    layouts[3]->parent()->setObjectName(QString::number(3));
    layouts[4] = ui->gridLayout_5;
    layouts[4]->parent()->setObjectName(QString::number(4));
    layouts[5] = ui->gridLayout_6;
    layouts[5]->parent()->setObjectName(QString::number(5));
    layouts[6] = ui->gridLayout_7;
    layouts[6]->parent()->setObjectName(QString::number(6));
    layouts[7] = ui->gridLayout_8;
    layouts[7]->parent()->setObjectName(QString::number(7));
    layouts[8] = ui->gridLayout_9;
    layouts[8]->parent()->setObjectName(QString::number(8));



    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            QString text = "";
            //        itemButtons[i] = new QPushButton();
            //        connect(itemButtons[i],SIGNAL(clicked()),this,SLOT(itemClicked()));
            itemButtons[i][j] = createButton(text,SLOT(itemClicked()));
            itemButtons[i][j]->setObjectName(QString::number(j));
        }
    }



    for(int j=0; j<9; j++)
        for(int i=0; i<9; i++){
            int row = i/3;
            int column = i%3;
            if(i / 9 == 0)
                layouts[0]->addWidget(itemButtons[0][i],row,column);
            if(i / (9*2) == 0)
                layouts[1]->addWidget(itemButtons[1][i],row,column);
            if(i / (9*3) == 0)
                layouts[2]->addWidget(itemButtons[2][i],row,column);
            if(i / (9*4) == 0)
                layouts[3]->addWidget(itemButtons[3][i],row,column);
            if(i / (9*5) == 0)
                layouts[4]->addWidget(itemButtons[4][i],row,column);
            if(i / (9*6) == 0)
                layouts[5]->addWidget(itemButtons[5][i],row,column);
            if(i / (9*7) == 0)
                layouts[6]->addWidget(itemButtons[6][i],row,column);
            if(i / (9*8) == 0)
                layouts[7]->addWidget(itemButtons[7][i],row,column);
            if(i / (9*9) == 0)
                layouts[8]->addWidget(itemButtons[8][i],row,column);
        }





}


QPushButton *MainWindow::createButton(QString &text, const QString member/*const char *member*/){
    //Creates button and sets size policy. Connects button's signal to slot

    QPushButton *button = new QPushButton;
    button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    button->setText(text);
    button->setCheckable(true);
    button->setAutoExclusive(true);

    connect(button, SIGNAL(clicked()),this,member.toStdString().c_str()); //connect button signal to SLOT(itemClicked)
    return button;
}

void MainWindow::itemClicked(){
    //Slot for when a tile has been clicked.

    QPushButton *clickedItem = qobject_cast<QPushButton*>(sender());

    qDebug() << "objectName: " << clickedItem->parent()->objectName();

    qDebug() << "ItemClicked: " << clickedItem->objectName().toInt();
    qDebug() << "currentGrid: " << currentGrid << endl;
    qDebug() << "nextGrid: " << nextGrid << endl;
    clickedItem->setAutoExclusive(false);
    clickedItem->setChecked(false);
    clickedItem->setAutoExclusive(true);

    currentGrid = clickedItem->parent()->objectName().toInt();



    //Read user symbol, and set button to that symbol
    if(humanTurn && game->isLegal(clickedItem->objectName().toInt(),currentGrid)){
        clickedItem->setText(QString(QChar(game->gridChar(game->human))));

        game->humanMove(clickedItem->objectName().toInt(),currentGrid);
        nextGrid = clickedItem->objectName().toInt();

        qDebug() << "Check WINNER (After Human Move): ";
        qDebug() << "currentGrid: " << currentGrid;
        qDebug() << "nextGrid: " << nextGrid;
        //Check if player has won.
        CheckWinner();

    }
    else if(!game->isLegal(clickedItem->objectName().toInt(),currentGrid))
        invalidMove();
}

void MainWindow::begin(){
    //Sets player character. Calls TicTacToe::Play()
    //The Game begins.

    QString text = "You are playing as " + QString(QChar(options->getChar()));
    if(options->getChar() == 'O'){

        text.append(". Computer moves first.");
        //game->human = 'O';
        game->human = -1;

        //Computer makes move
        //game->computerMove(game->opponent(game->human));
        game->computerMax();
    }
    else{
        text.append(". Select a square.");
        //game->human = 'X';
        game->human = -1;
        humanTurn = true;
    }

    ui->announce->setText(text);


    //Begin game
    //game->Play();


}

void MainWindow::humanMoves(){

    humanTurn = true;
    ui->announce->setText("Make a move.");
}

void MainWindow::computerMove(int move,int grid){
    qDebug() << "ComputerMove: " << move;
    qDebug() << "nextGrid: " << nextGrid;
    qDebug() << "grid: " << grid;

    if(grid != -1)
        nextGrid = grid;


    humanTurn = false;
    itemButtons[nextGrid][move]->setText(QString(QChar(game->gridChar(game->opponent(game->human)))));

    //Check if computer has won
    CheckWinner();

    nextGrid = move;
    qDebug() << "Player must move here: " << nextGrid;
}

void MainWindow::CheckWinner(){

    qDebug() << "Winner is " << game->winner(nextGrid) << " at " << nextGrid;

    QString announce;
    if(game->winner(nextGrid) == game->human){
        game->setGridState(nextGrid,game->human);
        ui->announce->setText("You have won!");
        humanTurn = false; //Disable clicking
        ui->playAgain->setVisible(true);
        //return;
    }
    else if(game->winner(nextGrid) == game->opponent(game->human)){
        game->setGridState(nextGrid,1);
        ui->announce->setText("You have lost!");
        qDebug() << "COMPUTER WON AT " << nextGrid;
        ui->playAgain->setVisible(true);
        //return;
    }
    else if(game->winner(nextGrid) == 0){
        announce = "TIE! on board" + QString::number(currentGrid);
        ui->announce->setText(announce);
        ui->playAgain->setVisible(true);
        return;
    }

    //Now check ultimate win
    else if(game->ultWin() == game->human)
        qDebug() << "HUMAN WIN";
    else if(game->ultWin() == game->opponent(game->human))
        qDebug() << "COMPUTER WIN";

    if(humanTurn)
        game->CalculateGrid(nextGrid);
        //game->computerMax();
    //game->computerMove(game->opponent(game->human));
    else{
        humanMoves();
    }
}

void MainWindow::invalidMove(){
    ui->announce->setText("Invalid move! Try again.");
    qDebug() << "currentGrid: " << currentGrid;
    qDebug() << "nextGrid: " << nextGrid;
}

void MainWindow::on_playAgain_clicked()
{
    for(int i=0; i<9; i++)
        itemButtons[4][i]->setText("");

    game->reset();
    begin();

    ui->playAgain->setVisible(false);

}

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

    game->moveToThread(pthread);


    connect(options,SIGNAL(choosen(int)),this,SLOT(begin(int)));
    connect(game,SIGNAL(humanMoves()),this,SLOT(humanMoves()));
    connect(game,SIGNAL(computerMove(int,int)),this,SLOT(computerMove(int,int)));
    connect(game,SIGNAL(prediction(QString)),this,SLOT(prediction(QString)));



    connect(transit,SIGNAL(display(QString)),this,SLOT(prediction(QString)));
    connect(transit,SIGNAL(computerMove(int,int,int,int)),this,SLOT(computerMove(int,int,int,int)));
    newgame.transit = transit; //Connect Game's transmitter to Mainwindow's transmitter

    pthread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpGrid(){




    frames[0] = ui->gridFrame;
    frames[1] = ui->gridFrame_2;
    frames[2] = ui->gridFrame_3;
    frames[3] = ui->gridFrame_4;
    frames[4] = ui->gridFrame_5;
    frames[5] = ui->gridFrame_6;
    frames[6] = ui->gridFrame_7;
    frames[7] = ui->gridFrame_8;
    frames[8] = ui->gridFrame_9;


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

int MainWindow::itemClicked(){
    //Slot for when a tile has been clicked.

    QPushButton *clickedItem = qobject_cast<QPushButton*>(sender());

    clickedItem->setAutoExclusive(false);
    clickedItem->setChecked(false);
    clickedItem->setAutoExclusive(true);

    currentGrid = clickedItem->parent()->objectName().toInt();

    if(currentGrid != nextGrid && nextGrid != -1 && !wonGrids[nextGrid]){
        qDebug() << "NOPE";
        invalidMove();
        return -1;
    }

    //Read user symbol, and set button to that symbol
    if(humanTurn && game->isLegal(clickedItem->objectName().toInt(),currentGrid) && !wonGrids[currentGrid]){

        clickedItem->setText(QString(QChar(game->gridChar(game->human))));        //Sets pushbutton text to player's char.

        game->humanMove(clickedItem->objectName().toInt(),currentGrid);           //Sets subBoard with player's char


        CheckWinner(currentGrid);
        player = 1;

        nextGrid = clickedItem->objectName().toInt();                             //next move for computer will need to be where player sent it to.


       // emit computer_(nextGrid,1);
        QFuture<void> future = QtConcurrent::run(this,&MainWindow::computer,nextGrid,1);
        //game->CalculateGrid(nextGrid,1);
        qDebug() << "RETURN: ";

    }
    //else if(!game->isLegal(clickedItem->objectName().toInt(),currentGrid))
        //invalidMove();


    int board = clickedItem->parentWidget()->objectName().toInt();
    int board_row =  board / 3;
    int board_col = board % 3;
    int cell_row = clickedItem->objectName().toInt();
    int cell_col = clickedItem->objectName().toInt();

    qDebug() << "board_row: " << board_row << " board_col: " << board_col << endl;
    qDebug() << "cell_row: " << cell_row << " cell_col: " << cell_col << endl;

    //newgame.PlayCell(board_row,board_col,cell_row,cell_col);
    //computerMoves();
}

void MainWindow::begin(int strength){
    //Sets player character. Calls TicTacToe::Play()
    //The Game begins.

    QString text = "You are playing as " + QString(QChar(options->getChar()));
    this->strength = strength;
    game->setDepth(strength);


    //newgame.transit->displayMessage("LOL");

    if(options->getChar() == 'O'){
        text.append(". Computer moves first.");
        player = 1;
        //game->CalculateGrid(4,1); //Computer moves.
        computerMoves();

    }
    else{
        text.append(". Select a square.");
        humanTurn = true;
        player = -1;
    }

    ui->announce->setText(text);

}

void MainWindow::humanMoves(){

    humanTurn = true;
    ui->announce->setText("Make a move.");

}


void MainWindow::computerMove(int board_row, int board_col, int cell_row, int cell_col){

    int grid = board_row * 3 + board_col;
    int slot = cell_row * 3 + cell_col;

    itemButtons[grid][slot]->setText(QString(QChar('O')));
    itemButtons[grid][slot]->setStyleSheet("background-color: yellow");

}

void MainWindow::CheckWinner(int grid){

    QString announce;
    if(game->winner(grid) == -1){
        game->setGridState(grid,-1);

        qDebug() << "PLAYER WON AT " << grid;

        humanTurn = false; //Disable clicking

        wonGrids[grid] = -1;
        colorBoardWin(grid,-1);

        ui->playAgain->setVisible(true);
    }
    else if(game->winner(grid) == 1){
        game->setGridState(grid,1);

        qDebug() << "COMPUTER WON AT " << grid;

        wonGrids[grid] = 1;
        colorBoardWin(grid,1);

        ui->playAgain->setVisible(true);
    }
    else if(game->winner(grid) == -5){

        announce = "TIE! on board" + QString::number(grid);

        ui->announce->setText(announce);

        ui->playAgain->setVisible(true);
        return;
    }

    //Now check ultimate win
    if(game->ultWin() == -1)
        qDebug() << "HUMAN WIN";
    else if(game->ultWin() == 1){

        qDebug() << "COMPUTER WIN";

        frames[game->ultimateWinGrids[0]]->setStyleSheet("background-color: red");
        frames[game->ultimateWinGrids[1]]->setStyleSheet("background-color: red");
        frames[game->ultimateWinGrids[2]]->setStyleSheet("background-color: red");

    }

}

void MainWindow::invalidMove(){
    ui->announce->setText("Invalid move! Try again.");
    qDebug() << "currentGrid: " << currentGrid;
    qDebug() << "nextGrid: " << nextGrid;
}

void MainWindow::on_playAgain_clicked()
{

    //Clear all background colors,

    for(int i=0; i<9; i++){
        for(int j=0;j<9;j++){
            itemButtons[i][j]->setText("");
        }
    }

    for(int i=0; i<9; i++){
        frames[i]->setStyleSheet("background-color: none");
        wonGrids[i] = 0;
        for(int j=0; j<9; j++){
            itemButtons[i][j]->setStyleSheet("background-color: none");
        }
    }

    currentGrid = -1;
    nextGrid = -1;
    game->reset();
    begin(strength);

    ui->playAgain->setVisible(false);

}

void MainWindow::colorBoard(int nextGrid, int move){

    //itemButtons[nextGrid][move]->setStyleSheet("background-color: red");

    for(int i=0; i<9; i++){
        frames[i]->setStyleSheet("background-color: none");
    }

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){

            if(wonGrids[i] == EMPTY){
                itemButtons[i][j]->setStyleSheet("background-color: none");
            }
        }
    }


    //Sets computer move's background color
    QPushButton* button = itemButtons[nextGrid][move];
    QPalette pal = button->palette();
    pal.setColor(QPalette::Button, QColor(Qt::blue));
    button->setAutoFillBackground(true);
    button->setPalette(pal);
    button->update();

    itemButtons[nextGrid][move]->setStyleSheet("background-color: yellow");

    if(wonGrids[move] == EMPTY){
        frames[move]->setStyleSheet("background-color: lightgreen");
    }
    else{
        for(int i=0; i<9; i++){
            if(i != move)
                frames[i]->setStyleSheet("background-color: lightblue");
        }
    }



}

void MainWindow::colorBoardWin(int nextGrid,int player){



    if(player == -1){
        itemButtons[nextGrid][game->winningRows[0]]->setStyleSheet("background-color: lightblue");
        itemButtons[nextGrid][game->winningRows[1]]->setStyleSheet("background-color: lightblue");
        itemButtons[nextGrid][game->winningRows[2]]->setStyleSheet("background-color: lightblue");
    }
    else{
        itemButtons[nextGrid][game->winningRows[0]]->setStyleSheet("background-color: pink");
        itemButtons[nextGrid][game->winningRows[1]]->setStyleSheet("background-color: pink");
        itemButtons[nextGrid][game->winningRows[2]]->setStyleSheet("background-color: pink");
    }



}

void MainWindow::colorBoardUltimateWin(int player){

    //for(int i=0; i<)
}

void MainWindow::computer(int grid,int player){

    double time;
    humanTurn = false; //Prevent random clicking
    QTime myTimer;
    myTimer.start();
    //Qtconcurrent::run();
    ui->announce->setText("Thinking...");
    game->CalculateGrid(nextGrid,player);

    time = myTimer.elapsed();

    ui->timer->setText("Move took: " + QString::number(time/1000) + " seconds.");

    humanTurn = true;

    qDebug() << "Returned!!!";

}


void MainWindow::prediction(QString prediction){

    ui->predictor->setText(prediction);

}



//MonteCarlo

void MainWindow::computerMoves(){


    QTime myTimer;
    myTimer.start();

    montebot.botThinkingTime = 1000;

    montebot.StartCalculation(newgame);
    qDebug() << "Finished computer move";

    while(myTimer.elapsed() < montebot.botThinkingTime){
        montebot.CalculateAhead(newgame);
    }

    qDebug() << "BOT PLAYS";
    montebot.Play(newgame);
    qDebug() << "DONE";

}

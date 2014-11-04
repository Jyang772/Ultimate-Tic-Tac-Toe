#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    if(true){
    QApplication a(argc, argv);

    MainWindow w;
    w.show();




//    bool winner = false;
//    int currentGrid = -1;
//    w.player = -1;


//    while(!winner){

//        if(w.player == -1){
//            w.begin(2);
//            w.humanMoves();

//           //currentGrid = w.itemClicked();

//            w.player = 1;
//        }
//        else{
//            w.computer(currentGrid);
//            w.player = -1;
//        }


//        //Check for winner every turn
//        w.CheckWinner(currentGrid);
//    }






    return a.exec();
    }
    else
    {
        qDebug()  << "Console Mode.\n";
        std::cout << "Console Mode.\n";

        //Do stuff
    }


}

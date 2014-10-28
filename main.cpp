#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    std::cout << argv[1] << std::endl;

    //if(argc == 2 && !strcmp(argv[1],"-win")){
    if(true){
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
    }
    else
    {
        qDebug()  << "Console Mode.\n";
        std::cout << "Console Mode.\n";

        //Do stuff
    }


}

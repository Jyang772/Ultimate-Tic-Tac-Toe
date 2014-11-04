#include "transmitter.h"

Transmitter::Transmitter(QObject *parent) :
    QObject(parent)
{
}


void Transmitter::displayMessage(QString msg){

    emit display(msg);
}

void Transmitter::highlight(int board_row, int board_col, int cell_row, int cell_col){

    emit Win(board_row, board_col, cell_row, cell_col);
}

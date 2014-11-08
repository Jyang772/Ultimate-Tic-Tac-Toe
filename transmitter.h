#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <QObject>
#include "move.h"

class Transmitter : public QObject
{
    Q_OBJECT
public:
    explicit Transmitter(QObject *parent = 0);
    void displayMessage(QString);
    void highlight(int board_row, int board_col, int cell_row, int cell_col);

signals:
    void display(QString);
    void Win(int board_row, int board_col, int cell_row, int cell_col);
    void computerMove(int board_row, int board_col, int cell_row, int cell_col);
    void wonBoard(int board_row, int board_col, int player);

    void wonSlots(int board_row, int board_col, std::vector<Move>&);

public slots:


};

#endif // TRANSMITTER_H

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLayout>
#include <QLabel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    char getChar();
    ~Dialog();

signals:
    void choosen();


private slots:

    void on_chooseX_clicked();

    void on_chooseY_clicked();

private:
    Ui::Dialog *ui;
    char choosenChar;
    //QVBoxLayout *layout = new QVBoxLayout;

};

#endif // DIALOG_H

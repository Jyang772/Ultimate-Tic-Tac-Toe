#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
//    QLabel *label = new QLabel("Hello");
//    layout->addWidget(label,0,0);
//    layout->addWidget(ui->buttonBox);
//    setLayout(layout);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_chooseX_clicked()
{
    choosenChar = 'X';
    strength = ui->lineEdit->text().toInt();
    emit choosen(strength);
    close();
}

void Dialog::on_chooseY_clicked()
{
    choosenChar = 'O';
    strength = ui->lineEdit->text().toInt();
    emit choosen(strength);
    close();
}

char Dialog::getChar(){
    return choosenChar;
}




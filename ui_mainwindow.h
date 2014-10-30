/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *announce;
    QPushButton *playAgain;
    QWidget *widget;
    QGridLayout *gridLayout_11;
    QFrame *gridFrame;
    QGridLayout *gridLayout;
    QFrame *line_6;
    QFrame *gridFrame_8;
    QGridLayout *gridLayout_8;
    QFrame *line_5;
    QFrame *gridFrame_4;
    QGridLayout *gridLayout_4;
    QFrame *gridFrame_6;
    QGridLayout *gridLayout_6;
    QFrame *gridFrame_7;
    QGridLayout *gridLayout_7;
    QFrame *gridFrame_2;
    QGridLayout *gridLayout_2;
    QFrame *line_3;
    QFrame *gridFrame_5;
    QGridLayout *gridLayout_5;
    QFrame *gridFrame_9;
    QGridLayout *gridLayout_9;
    QFrame *line;
    QFrame *line_2;
    QFrame *gridFrame_3;
    QGridLayout *gridLayout_3;
    QFrame *line_4;
    QFrame *line_7;
    QFrame *line_8;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(851, 783);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        announce = new QLabel(centralWidget);
        announce->setObjectName(QStringLiteral("announce"));
        announce->setGeometry(QRect(30, 0, 351, 21));
        playAgain = new QPushButton(centralWidget);
        playAgain->setObjectName(QStringLiteral("playAgain"));
        playAgain->setGeometry(QRect(350, 670, 141, 27));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(130, 100, 641, 521));
        gridLayout_11 = new QGridLayout(widget);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        gridFrame = new QFrame(widget);
        gridFrame->setObjectName(QStringLiteral("gridFrame"));
        gridLayout = new QGridLayout(gridFrame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout_11->addWidget(gridFrame, 0, 0, 1, 1);

        line_6 = new QFrame(widget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        gridLayout_11->addWidget(line_6, 3, 3, 1, 1);

        gridFrame_8 = new QFrame(widget);
        gridFrame_8->setObjectName(QStringLiteral("gridFrame_8"));
        gridLayout_8 = new QGridLayout(gridFrame_8);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout_11->addWidget(gridFrame_8, 6, 2, 1, 1);

        line_5 = new QFrame(widget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout_11->addWidget(line_5, 3, 1, 1, 1);

        gridFrame_4 = new QFrame(widget);
        gridFrame_4->setObjectName(QStringLiteral("gridFrame_4"));
        gridLayout_4 = new QGridLayout(gridFrame_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout_11->addWidget(gridFrame_4, 3, 0, 1, 1);

        gridFrame_6 = new QFrame(widget);
        gridFrame_6->setObjectName(QStringLiteral("gridFrame_6"));
        gridLayout_6 = new QGridLayout(gridFrame_6);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout_11->addWidget(gridFrame_6, 3, 4, 1, 1);

        gridFrame_7 = new QFrame(widget);
        gridFrame_7->setObjectName(QStringLiteral("gridFrame_7"));
        gridLayout_7 = new QGridLayout(gridFrame_7);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout_11->addWidget(gridFrame_7, 6, 0, 1, 1);

        gridFrame_2 = new QFrame(widget);
        gridFrame_2->setObjectName(QStringLiteral("gridFrame_2"));
        gridLayout_2 = new QGridLayout(gridFrame_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout_11->addWidget(gridFrame_2, 0, 2, 1, 1);

        line_3 = new QFrame(widget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_11->addWidget(line_3, 0, 1, 1, 1);

        gridFrame_5 = new QFrame(widget);
        gridFrame_5->setObjectName(QStringLiteral("gridFrame_5"));
        gridLayout_5 = new QGridLayout(gridFrame_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout_11->addWidget(gridFrame_5, 3, 2, 1, 1);

        gridFrame_9 = new QFrame(widget);
        gridFrame_9->setObjectName(QStringLiteral("gridFrame_9"));
        gridLayout_9 = new QGridLayout(gridFrame_9);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_9->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout_11->addWidget(gridFrame_9, 6, 4, 1, 1);

        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_11->addWidget(line, 1, 0, 1, 5);

        line_2 = new QFrame(widget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_11->addWidget(line_2, 4, 0, 1, 5);

        gridFrame_3 = new QFrame(widget);
        gridFrame_3->setObjectName(QStringLiteral("gridFrame_3"));
        gridLayout_3 = new QGridLayout(gridFrame_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout_11->addWidget(gridFrame_3, 0, 4, 1, 1);

        line_4 = new QFrame(widget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_11->addWidget(line_4, 0, 3, 1, 1);

        line_7 = new QFrame(widget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        gridLayout_11->addWidget(line_7, 6, 1, 1, 1);

        line_8 = new QFrame(widget);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        gridLayout_11->addWidget(line_8, 6, 3, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 851, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        announce->setText(QApplication::translate("MainWindow", "Announcement", 0));
        playAgain->setText(QApplication::translate("MainWindow", "Click to Play Again", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

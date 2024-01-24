
#include <QApplication>

#include "gameconfig.h"
#include "mainwindow.h"
#include "tictactoewidget.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //    TicTacToeWidget t;
    //    t.show();

    mainwindow ma;
    ma.show();
    //    gameconfig *gameConfig = gameconfig::getInstance();
    //    gameConfig->setPlayer1Name("jack");
    //
    //    gameConfig->setSide(5);
    //    gameConfig->show();
    int result = a.exec();
    // delete gameConfig;
    return result;
}

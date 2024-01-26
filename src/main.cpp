#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mainwindow mw;
    mw.show();
    int result = a.exec();

    return result;
}

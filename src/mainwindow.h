//
// Created by riki on 1/18/24.
//

#ifndef TIC_TAC_TOE_MAINWINDOW_H
#define TIC_TAC_TOE_MAINWINDOW_H
#include <QMainWindow>

#include "tictactoewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class mainwindow;
}
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    void createMenu();

    ~mainwindow() override;

private:
    Ui::mainwindow *ui;
};

#endif  // TIC_TAC_TOE_MAINWINDOW_H

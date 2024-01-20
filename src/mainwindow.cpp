#include "mainwindow.h"

#include <QFont>
#include <QKeySequence>
#include <QMenu>
#include <QShortcut>
#include <QToolBar>

#include "base.h"
#include "logger.h"
#include "ui_mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);

    this->createMenu();

    // styling labels
    QFont font(ui->p1_lbl->font().family(), 15, QFont::Normal);
    ui->p1_lbl->setFont(font);
    ui->p2_lbl->setFont(font);
    QString p1_style = "QLabel{color: " + MetaData::PLAYER_1_COLOR + "};";
    QString p2_style = "QLabel{color: " + MetaData::PLAYER_2_COLOR + "};";
    ui->p1_lbl->setStyleSheet(p1_style);
    ui->p2_lbl->setStyleSheet(p2_style);
}

mainwindow::~mainwindow() {
    delete ui;
}

/**
 * @brief create menu for mainwindow
 */
void mainwindow::createMenu() {
    auto *fileMenu = ui->menubar->addMenu("File");
    auto *newAction = new QAction(QIcon(":/resources/new.png"), tr("New"), this);
    auto *quitAction = new QAction(QIcon(":/resources/quit.png"), tr("Quit"), this);
    newAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    connect(newAction, &QAction::triggered, [=]() {
        logger(logger_level::INFO, "new action called");
    });

    connect(quitAction, &QAction::triggered, [=]() {
        QApplication::quit();
    });

    fileMenu->addAction(newAction);
    fileMenu->addAction(quitAction);

    // create a toolbar
    QToolBar *newToolBar = mainwindow::addToolBar("ToolBar");
    newToolBar->addAction(newAction);
    newToolBar->addSeparator();
    newToolBar->addAction(quitAction);
}

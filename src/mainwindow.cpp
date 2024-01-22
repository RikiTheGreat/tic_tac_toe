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
    : QMainWindow(parent), ui(new Ui::mainwindow), configuration{gameconfig::getInstance()} {
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

    connect(newAction, &QAction::triggered, this, &mainwindow::newGame);

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

/**
 * @brief represents a new game
 */
void mainwindow::newGame() noexcept {
    // reset players' names
    ui->p1_lbl->setText("");
    ui->p2_lbl->setText("");

    // reset game's side
    configuration->setSide(SideConfig::MIN_RANGE);

    // if player press cancel button, new game will be aborted
    if (configuration->exec() == QDialog::Rejected) {
        configuration->setPlayer1Name("");
        configuration->setPlayer2Name("");
        configuration->setSide(4);
        return;
    }


    // clear configuration fields
    configuration->setPlayer1Name("");
    configuration->setPlayer2Name("");
    configuration->setSide(5);


    // configuration for players' names
    ui->p1_lbl->setText(configuration->getPlayer1Name());
    ui->p2_lbl->setText(configuration->getPlayer2Name());

    auto side = configuration->getSide();

    // adjustment of the board
    ui->tictactoe->setFixedHeight(50 * (side));
    ui->tictactoe->setFixedWidth(50 * (side));
    ui->tictactoe->setSide(side);
    ui->title_lbl->setVisible(false);
    ui->tictactoe->setEnabled(true);

    ui->tictactoe->restartGame();
}

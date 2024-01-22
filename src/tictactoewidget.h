#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QGridLayout>
#include <QList>
#include <QPushButton>
#include <QSignalMapper>
#include <QWidget>

#include "base.h"

class TicTacToeWidget : public QWidget {
    Q_OBJECT

public:
    TicTacToeWidget(QWidget *parent = nullptr);
    ~TicTacToeWidget() override;

    [[nodiscard]] Player getPlayer() const noexcept;
    void setPlayer(Player newPlayer) noexcept;
    void resetBoard() noexcept;
    [[nodiscard("get the board")]] const QList<QPushButton *> getBoard() noexcept;

    void setSide(int gs);
    int getSide() const noexcept;
signals:
    void gameOver();

private:
    void createBoard();
    Winner determineWinner(Symbol sym, int buttonIndex);
    bool checkSymbol(Symbol sym, int index) noexcept;
    void emptyBoard();
private slots:
    void handleClickOnBoard(int id);
    void finishGame();
public slots:
    void restartGame();

private:
    QList<QPushButton *> board_list;
    QGridLayout *board_layout{};
    Player player;
    Winner winner;
    int gameSide;
};
#endif  // TICTACTOEWIDGET_H

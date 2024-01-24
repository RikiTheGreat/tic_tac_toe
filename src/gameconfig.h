#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <QAbstractButton>
#include <QDialog>

#include "base.h"

namespace Ui {
class gameconfig;
}

class gameconfig : public QDialog {
    Q_OBJECT

public:
    explicit gameconfig(QWidget *parent = nullptr);
    explicit gameconfig(Ui::gameconfig *ui)
        : ui(ui) {
    }
    ~gameconfig();

    // getters and setters for players
    QString getPlayer1Name() const noexcept;
    void setPlayer1Name(QString const &new_name);
    QString getPlayer2Name() const noexcept;
    void setPlayer2Name(QString const &new_name);

    // singleton function
    static gameconfig *getInstance();

    // setter and getter for sides
    int getSide() noexcept;
    void setSide(int sg);

    // get the mode of the game
    [[nodiscard]] Mode getMode() const noexcept;
    void setMode(Mode m);

public slots:
    void updateOnButton(QString const &str);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void aiMode_checked(bool checked);
    void twoPlayer_checked(bool checked);

    signals:
        void modeUpdated(Mode mode);
private:
    Ui::gameconfig *ui;
    static inline gameconfig *GameConfig = nullptr;
};

#endif  // GAMECONFIG_H

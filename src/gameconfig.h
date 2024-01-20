#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <QAbstractButton>
#include <QDialog>

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
    void setSide(int side);

public slots:
    void updateOnButton(QString const &str);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::gameconfig *ui;
    static inline gameconfig *GameConfig = nullptr;
};

#endif  // GAMECONFIG_H

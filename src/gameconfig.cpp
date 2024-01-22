#include "gameconfig.h"

#include <QPushButton>
#include <QSlider>

#include "base.h"
#include "logger.h"
#include "ui_gameconfig.h"

gameconfig::gameconfig(QWidget *parent)
    : QDialog(parent), ui(new Ui::gameconfig) {
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &gameconfig::updateOnButton);
    connect(ui->lineEdit2, &QLineEdit::textChanged, this, &gameconfig::updateOnButton);
    connect(ui->spinBox, &QSpinBox::valueChanged, ui->horizontalSlider, &QSlider::setValue);
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);

    // set base size for siders
    ui->spinBox->setRange(SideConfig::MIN_RANGE, SideConfig::MAX_RANGE);
    ui->horizontalSlider->setRange(SideConfig::MIN_RANGE, SideConfig::MAX_RANGE);

    // default mode for game
    ui->twoPlayerMode->setChecked(true);
}

gameconfig::~gameconfig() {
    delete ui;
}

/**
 * @brief gameconfig::getPlayer1Name
 * @return player1's name
 */
QString gameconfig::getPlayer1Name() const noexcept {
    return ui->lineEdit->text();
}

/**
 * @brief gameconfig::setPlayer1Name
 * @param new_name
 */
void gameconfig::setPlayer1Name(const QString &new_name) {
    ui->lineEdit->setText(new_name);
}

/**
 * @brief gameconfig::getPlayer2Name
 * @return  player2's name
 */
QString gameconfig::getPlayer2Name() const noexcept {
    return ui->lineEdit2->text();
}

/**
 * @brief gameconfig::setPlayer2Name
 * @param new_name
 */
void gameconfig::setPlayer2Name(const QString &new_name) {
    ui->lineEdit2->setText(new_name);
}

/**
 * @brief gameconfig::getInstance
 * @return gameconfig*
 * a function which returns a unique instance of gameconfig class
 */
gameconfig *gameconfig::getInstance() {
    if (GameConfig == nullptr) {
        GameConfig = new gameconfig();
    }

    return GameConfig;
}

/**
 * @brief gameconfig::getSide
 * @return int
 * returns value of spinbox and sliders -> side game
 */
int gameconfig::getSide() noexcept {
    return ui->spinBox->value();
}

/**
 * @brief gameconfig::setSide
 * @param size
 * set side game value
 */
void gameconfig::setSide(int sg) {
    if (sg > SideConfig::MAX_RANGE || sg < SideConfig::MIN_RANGE)
        return;

    ui->spinBox->setValue(sg);
}

/**
 * @brief gameconfig::updateOnButton
 * rules for ok button
 */
void gameconfig::updateOnButton(QString const &str) {
    bool le1 = ui->lineEdit->text().isEmpty();
    bool le2 = ui->lineEdit2->text().isEmpty();

    auto ok_btn = ui->buttonBox->button(QDialogButtonBox::Ok);
    if (le1 || le2)
        ok_btn->setDisabled(true);
    else
        ok_btn->setEnabled(true);
}

/**
 * @brief gameconfig::on_buttonBox_clicked
 * @param button
 * A function which handles the botton box on config window
 */
void gameconfig::on_buttonBox_clicked(QAbstractButton *button) {
    if (button == ui->buttonBox->button(QDialogButtonBox::Ok)) {
        if (ui->twoPlayerMode->isChecked()) {
            logger(logger_level::INFO, "two player mode selected");
        } else {
            logger(logger_level::INFO, "ai mode selected");
        }
    }
}

Mode gameconfig::getMode() const noexcept {
    if (ui->twoPlayerMode->isChecked()) {
        return Mode::TwoPlayer;
    } else {
        return Mode::AI;
    }
}

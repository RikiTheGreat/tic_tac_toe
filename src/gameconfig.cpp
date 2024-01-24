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
    connect(ui->AiMode, &QRadioButton::toggled, this, &gameconfig::aiMode_checked);
    connect(ui->twoPlayerMode, &QRadioButton::toggled, this, &gameconfig::twoPlayer_checked);
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
            logger(logger_level::INFO, "Two player mode selected");
        } else {
            logger(logger_level::INFO, "Ai mode selected");
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

/**
 * when user checked ai mode radio button do something
 * @brief gameconfig::on_AiMode_checked
 */
void gameconfig::aiMode_checked(bool checked) {
    if(checked) {
        ui->lineEdit2->setText(MetaData::AI_NAME);
        ui->lineEdit2->setDisabled(true);
    }
}

/**
 * when user checked two player mode radio button do something
 * @brief gameconfig::on_TwoPlayer_checked()
 */
void gameconfig::twoPlayer_checked(bool checked)  {
    if(checked) {
        ui->lineEdit2->setText("");
        ui->lineEdit2->setDisabled(false);
    }
}

/**
 * @brief set game mode
 * @param m
 */
void gameconfig::setMode(Mode m) {
    if(m == Mode::AI)
        ui->AiMode->setChecked(true);
    else
        ui->twoPlayerMode->setChecked(true);

    emit modeUpdated(m);
}

#include "tictactoewidget.h"

#include <QFont>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>
#include <QVBoxLayout>

#include "logger.h"

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget(parent), player{Player::player1}, winner{Winner::noWinnerYet}

{
    connect(this, &TicTacToeWidget::gameOver, this, &TicTacToeWidget::finishGame);
    createBoard();
}

TicTacToeWidget::~TicTacToeWidget() = default;

/**
 * @brief TicTacToeWidget::createBoard
 * initialization of the game
 */
void TicTacToeWidget::createBoard() {
    board_layout = new QGridLayout(this);

    for (int row{}; row < MetaData::ROWS; ++row) {
        for (int col{}; col < MetaData::COLUMNS; ++col) {
            auto btn = new QPushButton("", this);
            btn->setMinimumSize(50, 50);
            board_layout->addWidget(btn, row, col);
            auto mapper = new QSignalMapper(this);
            // setMapping method gives an id to each sender, we need it for handling click on the board
            mapper->setMapping(btn, board_list.size());
            connect(btn, SIGNAL(clicked(bool)), mapper, SLOT(map()));
            connect(mapper, &QSignalMapper::mappedInt, this, &TicTacToeWidget::handleClickOnBoard);

            board_list.append(btn);
        }
    }
}

Winner TicTacToeWidget::determineWinner(Symbol sym, int buttonIndex) {
    // step1: get the row and coulmn number of clicked button in the grid
    int rowNumber{buttonIndex / MetaData::COLUMNS};
    int colNumber{buttonIndex % MetaData::COLUMNS};

    // counting variable
    int counter{};

    // horizontal check
    // forward check
    bool validateSecondCheck{true};
    int newCol = colNumber;

    while (++newCol < MetaData::COLUMNS) {
        // position of the next button in the board
        int newPosition = rowNumber * MetaData::COLUMNS + newCol;

        validateSecondCheck = checkSymbol(sym, newPosition);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // backward check
    newCol = colNumber;  // reset the index
    while (validateSecondCheck && --newCol >= 0) {
        // position of the next button in the board
        int newPosition = rowNumber * MetaData::COLUMNS + newCol;
        validateSecondCheck = checkSymbol(sym, newPosition);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // horizontal win
    if (++counter == MetaData::COLUMNS) {
        if (sym == Symbol::X)
            return Winner::player1;
        else if (sym == Symbol::O)
            return Winner::player2;
    }

    // vertical check, upward and backward
    counter = 0;
    validateSecondCheck = true;
    int newRow = rowNumber;

    // backward check
    while (--newRow >= 0) {
        // position of the next button in the board
        int newPositionIndex = newRow * MetaData::COLUMNS + colNumber;

        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // upward check
    newRow = rowNumber;  // reset the index
    while (validateSecondCheck && ++newRow < MetaData::ROWS) {
        // position of the next button in the board
        int newPositionIndex = newRow * MetaData::COLUMNS + colNumber;
        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    if (++counter == MetaData::ROWS) {
        if (sym == Symbol::X)
            return Winner::player1;
        else if (sym == Symbol::O)
            return Winner::player2;
    }

    // backslash diagonal check
    // upward direction
    counter = 0;
    validateSecondCheck = true;
    newRow = rowNumber;
    newCol = colNumber;
    while (--newRow >= 0 && --newCol >= 0) {
        // get the position index of next position
        int newPositionIndex = newRow * MetaData::COLUMNS + newCol;
        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // downward check
    newRow = rowNumber;
    newCol = colNumber;
    while (validateSecondCheck && ++newRow < MetaData::ROWS && ++newCol < MetaData::COLUMNS) {
        // position of the next button in the board
        int newPositionIndex = newRow * MetaData::COLUMNS + newCol;
        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // did the player win diagonaly? (backslash direction)
    if (++counter == MetaData::ROWS) {
        if (sym == Symbol::X)
            return Winner::player1;
        else if (sym == Symbol::O)
            return Winner::player2;
    }

    // forward diagonal check
    // upward check
    counter = 0;
    validateSecondCheck = true;
    newRow = rowNumber;
    newCol = colNumber;

    while (--newRow >= 0 && ++newCol < MetaData::ROWS) {
        // position of the next button in the board
        int newPositionIndex = newRow * MetaData::COLUMNS + newCol;
        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // downward check
    newRow = rowNumber;
    newCol = colNumber;
    while (validateSecondCheck && ++newRow < MetaData::ROWS && --newCol >= 0) {
        // position of the next button in the board
        int newPositionIndex = newRow * MetaData::COLUMNS + newCol;
        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // did the player win diagonaly? (backslash direction)
    if (++counter == MetaData::ROWS) {
        if (sym == Symbol::X)
            return Winner::player1;
        else if (sym == Symbol::O)
            return Winner::player2;
    }

    // check for draw
    bool check_draw = true;
    for (int i = 0; i < MetaData::BOARD_SIZE; ++i)
        if (board_list.at(i)->text() == "")
            check_draw = false;

    return (check_draw) ? Winner::draw : Winner::noWinnerYet;
}

bool TicTacToeWidget::checkSymbol(Symbol sym, int index) noexcept {
    auto btn = this->board_list.at(index);

    QString symbol = (sym == Symbol::O) ? "O" : "X";
    if (btn->text() != symbol)
        return false;

    return true;
}

/**
 * @brief TicTacToeWidget::emptyBoard
 */
void TicTacToeWidget::emptyBoard() {
    // remove all buttons from window
    auto layout = this->layout();
    QLayoutItem *child;
    while (layout != nullptr && (child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    delete layout;
    board_list.clear();
}

void TicTacToeWidget::handleClickOnBoard(int id) {
    if (id < 0 || id > this->board_list.size()) {
        logger(logger_level::WARN, "Bad ID");
        return;
    }

    auto font = QFont(this->font().family(), 20, QFont::Bold);
    auto *btn = this->board_list.at(id);
    Symbol symbol;
    btn->setFont(font);
    if (player == Player::player1) {
        btn->setStyleSheet("QPushButton{ color: " + MetaData::PLAYER_1_COLOR + ";background: gray}");
        btn->setText("X");
        symbol = Symbol::X;
        btn->setDisabled(true);
    } else {
        btn->setStyleSheet("QPushButton{ color: " + MetaData::PLAYER_2_COLOR + "; background: dark}");
        btn->setText("O");
        symbol = Symbol::O;
        btn->setDisabled(true);
    }

    // determine the winner
    winner = determineWinner(symbol, id);
    if (winner == Winner::noWinnerYet) {
        if (getPlayer() == Player::player1)
            setPlayer(Player::player2);
        else
            setPlayer(Player::player1);

    } else if (winner == Winner::draw) {
        qInfo() << "Draw";
        QTimer::singleShot(MetaData::FREEZE_TIME, this, &TicTacToeWidget::gameOver);

    } else {
        // make the game to stop
        this->setDisabled(true);
        if (winner == Winner::player1)
            logger(logger_level::INFO, "Player1 is the winner");
        else if (winner == Winner::player2)
            logger(logger_level::INFO, "Player2 is the winner");

        QTimer::singleShot(MetaData::FREEZE_TIME, this, &TicTacToeWidget::gameOver);
    }
}

void TicTacToeWidget::finishGame() {
    emptyBoard();
    this->setEnabled(true);
    // create a vlayout to show result of game
    auto vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignCenter);

    QLabel *lbl_restart = new QLabel("text", this);
    QPushButton *btn_restart = new QPushButton("restart", this);
    QString lbl_btn_color;

    if (winner == Winner::player1) {
        lbl_btn_color = "color: " + MetaData::PLAYER_1_COLOR + ";";
    } else if (winner == Winner::player2) {
        lbl_btn_color = "color: " + MetaData::PLAYER_2_COLOR + ";";
    } else if (winner == Winner::draw) {
        lbl_btn_color = "color: " + MetaData::DRAW_COLOR + ";";
    }

    // set font and style
    QFont font(this->font().family(), 20, QFont::Bold);
    lbl_restart->setFont(font);
    btn_restart->setFont(font);
    lbl_restart->setStyleSheet(lbl_btn_color);
    btn_restart->setStyleSheet(lbl_btn_color);

    // connecting btn to restartGame slot
    connect(btn_restart, &QPushButton::clicked, this, &TicTacToeWidget::restartGame);

    vLayout->addWidget(lbl_restart);
    vLayout->addWidget(btn_restart);
}

/**
 * @brief TicTacToeWidget::restartGame
 */
void TicTacToeWidget::restartGame() {
    emptyBoard();
    this->setEnabled(true);
    createBoard();
}

/**
 * @brief TicTacToeWidget::getPlayer
 * @return current player
 */
Player TicTacToeWidget::getPlayer() const noexcept {
    return player;
}

/**
 * @brief TicTacToeWidget::setPlayer
 * @param newPlayer
 */
void TicTacToeWidget::setPlayer(Player newPlayer) noexcept {
    player = newPlayer;
}

/**
 * @brief TicTacToeWidget::resetBoard
 * clears all buttons
 */
void TicTacToeWidget::resetBoard() noexcept {
    for (auto &b : this->board_list)
        b->setText("");
}

/**
 * @brief TicTacToeWidget::getBoard()
 * @return const QList<QPushButton *> board_list
 */
const QList<QPushButton *> TicTacToeWidget::getBoard() noexcept {
    return this->board_list;
}

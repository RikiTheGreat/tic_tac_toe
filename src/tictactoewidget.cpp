#include "tictactoewidget.h"

#include <QFont>
#include <QLabel>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTimer>
#include <QVBoxLayout>
#include <memory>

#include "ai.h"
#include "logger.h"

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget(parent), player{Player::player1}, winner{Winner::noWinnerYet}, gameSide(SideConfig::MIN_RANGE),
      mode{Mode::AI}

{
    connect(this, &TicTacToeWidget::gameOver, this, &TicTacToeWidget::finishGame);
    connect(this, &TicTacToeWidget::sendAiMoves, this, &TicTacToeWidget::handleClickOnBoard);
    connect(this, &TicTacToeWidget::triggerAi, this, &TicTacToeWidget::triggerAiMoveCalculation);
    connect(this, &TicTacToeWidget::startAiMoveCalculation, this,
            &TicTacToeWidget::calculateAiMoves);
    connect(this, &TicTacToeWidget::startGPTMoveCalculation, this, &TicTacToeWidget::calculateGPTMoves);
}

TicTacToeWidget::~TicTacToeWidget() = default;

/**
 * @brief TicTacToeWidget::createBoard
 * initialization of the game
 */
void TicTacToeWidget::createBoard() {
    board_layout = new QGridLayout(this);

    for (int row{}; row < gameSide; ++row) {
        for (int col{}; col < gameSide; ++col) {
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
    // step1: get the row and column number of clicked button in the grid
    int rowNumber{buttonIndex / gameSide};
    int colNumber{buttonIndex % gameSide};

    // counting variable
    int counter{};

    // horizontal check
    // forward check
    bool validateSecondCheck{true};
    int newCol = colNumber;

    while (++newCol < gameSide) {
        // position of the next button in the board
        int newPosition = rowNumber * gameSide + newCol;

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
        int newPosition = rowNumber * gameSide + newCol;
        validateSecondCheck = checkSymbol(sym, newPosition);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // horizontal win
    if (++counter == gameSide) {
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
        int newPositionIndex = newRow * gameSide + colNumber;

        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // upward check
    newRow = rowNumber;  // reset the index
    while (validateSecondCheck && ++newRow < gameSide) {
        // position of the next button in the board
        int newPositionIndex = newRow * gameSide + colNumber;
        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    if (++counter == gameSide) {
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
        int newPositionIndex = newRow * gameSide + newCol;
        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // downward check
    newRow = rowNumber;
    newCol = colNumber;
    while (validateSecondCheck && ++newRow < gameSide && ++newCol < gameSide) {
        // position of the next button in the board
        int newPositionIndex = newRow * gameSide + newCol;
        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // did the player win diagonaly? (backslash direction)
    if (++counter == gameSide) {
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

    while (--newRow >= 0 && ++newCol < gameSide) {
        // position of the next button in the board
        int newPositionIndex = newRow * gameSide + newCol;
        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // downward check
    newRow = rowNumber;
    newCol = colNumber;
    while (validateSecondCheck && ++newRow < gameSide && --newCol >= 0) {
        // position of the next button in the board
        int newPositionIndex = newRow * gameSide + newCol;
        validateSecondCheck = checkSymbol(sym, newPositionIndex);
        if (!validateSecondCheck)
            break;
        else
            counter++;  // count the symbol on the next button
    }

    // did the player win diagonally? (backslash direction)
    if (++counter == gameSide) {
        if (sym == Symbol::X)
            return Winner::player1;
        else if (sym == Symbol::O)
            return Winner::player2;
    }

    // check for draw
    bool check_draw = true;
    for (int i = 0; i < gameSide * gameSide; ++i)
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
        logger("Bad ID", logger_level::WARN);
        return;
    }

    auto font = QFont(this->font().family(), 20, QFont::Bold);
    auto *btn = this->board_list.at(id);
    Symbol symbol;
    btn->setFont(font);
    if (player == Player::player1) {
        player1LastMove = id;
        player1Moves.push_back(player1LastMove);
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
        if (getPlayer() == Player::player1) {
            setPlayer(Player::player2);
            emit changePlayer();
        } else {
            setPlayer(Player::player1);
            emit changePlayer();
        }

    } else if (winner == Winner::draw) {
        emit determineOutCome();
        QTimer::singleShot(MetaData::FREEZE_TIME, this, &TicTacToeWidget::gameOver);

    } else {
        // make the game to stop
        this->setDisabled(true);
        if (winner == Winner::player1) {
            emit determineOutCome();
        } else if (winner == Winner::player2) {
            emit determineOutCome();
        }

        QTimer::singleShot(MetaData::FREEZE_TIME, this, &TicTacToeWidget::gameOver);
    }
}

void TicTacToeWidget::finishGame() {
    emptyBoard();
    this->setEnabled(true);
    // create a vlayout to show result of game
    auto vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignCenter);

    QLabel *lbl_restart = new QLabel(outComeMessage, this);
    lbl_restart->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

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
    this->setMinimumWidth(MetaData::END_GAME_WITH);
}

/**
 * @brief TicTacToeWidget::restartGame
 */
void TicTacToeWidget::restartGame(int size) {
    static int side{};
    if (!size && !side) {
        side = size;
    }
    this->setMinimumWidth(50 * side);
    player = Player::player1;
    emit changePlayer();

    if (mode == Mode::AI || mode == Mode::GPT)
        clearContainers();

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
    if (mode == Mode::AI || mode == Mode::GPT)
        emit triggerAi();
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

/**
 * @brief TicTacToeWidget::setSide
 * @param gs
 */
void TicTacToeWidget::setSide(int gs) {
    gameSide = gs;
}

/**
 * @brief TicTacToeWidget::getSide
 * @return gameSide
 */
int TicTacToeWidget::getSide() const noexcept {
    return gameSide;
}

/**
 * @brief  TicTacToeWidget::getOutCome()
 * @return winner
 */
Winner TicTacToeWidget::getOutCome() const noexcept {
    return winner;
}

/**
 * set outcome message
 * @brief TicTacToeWidget::setOutComeMessage
 * @param msg
 */
void TicTacToeWidget::setOutComeMessage(const QString &msg) {
    outComeMessage = msg;
}

/**
 * @brief TicTacToeWidget::updateMode
 * @param mode
 */
void TicTacToeWidget::updateMode(Mode m) {
    this->mode = m;
}

/**
 * @brief TicTacToeWidget::getMode()
 */
Mode TicTacToeWidget::getMode() const noexcept {
    return mode;
}

/**
 * remove Player and Ai moves
 * @brief TicTacToeWidget::clearContainers
 */
void TicTacToeWidget::clearContainers() {
    player1Moves.clear();
    aiMoves.clear();
}

/**
 * trigger ai calculation
 * @brief TicTacToeWidget::triggerAiMoveCalculation
 */
void TicTacToeWidget::triggerAiMoveCalculation() {
    if (player == Player::player2) {
        this->setDisabled(true);
        // delay for Ai to decide for his/her move
        if (mode == Mode::AI)
            QTimer::singleShot(MetaData::AI_DELAY, this, &TicTacToeWidget::startAiMoveCalculation);
        else if (mode == Mode::GPT)
            QTimer::singleShot(MetaData::AI_DELAY, this, &TicTacToeWidget::startGPTMoveCalculation);
    } else {
        this->setEnabled(true);
    }
}

/**
 * @brief TicTacToeWidget::calculateGPTMoves
 */
void TicTacToeWidget::calculateGPTMoves() {
    Ai ai{};
    auto result = ai.start_ai(player1Moves, aiMoves, gameSide);
    aiMoves.push_back(result);
    emit sendAiMoves(result);
}

/**
 * easy mode
 * @brief TicTacToeWidget::calculateAiMoves
 */

void TicTacToeWidget::calculateAiMoves() {
    quint32 randomNum = QRandomGenerator::global()->bounded(gameSide * gameSide);

    while (randomNum > (gameSide * gameSide) || player1Moves.contains(randomNum) || aiMoves.contains(randomNum)) {
        randomNum = QRandomGenerator::global()->bounded(gameSide * gameSide);
    }
    aiMoves.push_back(randomNum);
    emit sendAiMoves(randomNum);
}

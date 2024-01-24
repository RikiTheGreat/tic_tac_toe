#ifndef BASE_H
#define BASE_H

#include <QString>

/**
 * @brief The MetaData class
 * represents number of rows and columns for board
 */
struct MetaData {
    static inline QString PLAYER_1_COLOR{"cyan"};
    static inline QString PLAYER_2_COLOR{"red"};
    static inline QString DRAW_COLOR{"yellow"};
    static constexpr int FREEZE_TIME = 2000;  // 2 sec
    static constexpr int END_GAME_WITH = 500;
    static inline  QString AI_NAME = "Master Ai";
    static constexpr int AI_DELAY = 1000;
};

/**
 * @brief The SideConfig class
 * basic configuration for sides in gameconfig
 */
struct SideConfig {
    static constexpr int MIN_RANGE = 3;
    static constexpr int MAX_RANGE = 10;
};

/**
 * @brief The Player enum
 * player info
 */
enum class Player { player1,
                    player2 };

/**
 * @brief The Winner enum
 * an enum which represents the winner of the game
 */
enum class Winner { player1,
                    player2,
                    draw,
                    noWinnerYet };

/**
 * @brief The Symbol enum
 */
enum class Symbol { X,
                    O };

/**
 * @brief logger_level
 */
enum class logger_level {
    INFO,
    WARN,
    ERROR
};

/**
 * @brief represents the mode of the game
 */
enum class Mode {
    AI,
    TwoPlayer
};
#endif  // BASE_H

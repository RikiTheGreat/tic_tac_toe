//
// Created by riki on 1/26/24.
//

#include "ai.h"

#include <QDir>
#include <QFile>
#include <string>

#include "logger.h"
#include "path.h"

// #define TTT_DEBUG_MODE

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

Ai::Ai() {
    QDir::setCurrent(QString(PATH_STRING));
    QFile file("openai_api_key.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        logger(file.errorString(), logger_level::ERROR);
        exit(-1);
    }

    QTextStream in(&file);
    KEY = in.readLine();
    if (KEY.isEmpty()) {
        logger("openai_api_key.txt is empty!", logger_level::ERROR);
        exit(-1);
    }

    logger("You key: " + KEY);
}

/**
 * use openai API for gpt-mode
 * @brief Ai::start_ai
 * @param playerMoves
 * @param aiMoves
 * @param side
 * @return ai_move
 */
int Ai::start_ai(QList<int> const &playerMoves, QList<int> const &aiMoves, int side) {
    openai::start(KEY.toStdString());

    std::string msg = "You are the best tic tac toe player and we are playing " + std::to_string(side) + "*" + std::to_string(side) + " tic tac toe game."
                                                                                                                                      "game starts from index 0. my choices are index ";

    if (playerMoves.isEmpty()) {
        logger("no player1 move", logger_level::ERROR);
    }

    foreach (int num, playerMoves) {
        msg += std::to_string(num) + " ";
    }

    msg += ". ";

    if (aiMoves.isEmpty()) {
        msg += "now its your turn which index do you choose? please no explanation just return an integer";
    } else {
        msg += "your previous choices are ";
        foreach (int num, aiMoves)
            msg += std::to_string(num) + " ";

        msg += "now its your turn which index do you choose?j please no explanation just return an integer";
    }

#ifdef TTT_DEBUG_MODE
    logger(msg.data());
#endif

    ordered_json j;
    j["model"] = "gpt-3.5-turbo";
    j["messages"] = ordered_json::array({{{"role", "user"}, {"content", msg}}});
    j["max_tokens"] = 7;
    j["temperature"] = 0;

    auto chat = openai::chat().create(j);

#ifdef TTT_DEBUG_MODE
    std::cout << chat.dump(2);
#endif

    json Doc{json::parse(chat.dump(2))};
    auto raw_result = Doc["choices"][0]["message"]["content"];
    auto result = raw_result.front().get<std::string>();

    return std::stoi(result);
}

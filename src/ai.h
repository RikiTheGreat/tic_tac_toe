//
// Created by riki on 1/26/24.
//

#ifndef TIC_TAC_TOE_AI_H
#define TIC_TAC_TOE_AI_H

#include <QList>

#include "openai.hpp"

class Ai {
public:
    Ai();

    int start_ai(QList<int> const &playerMoves, QList<int> const &aiMoves, int side);

private:
    QString KEY;
};
#endif  // TIC_TAC_TOE_AI_H

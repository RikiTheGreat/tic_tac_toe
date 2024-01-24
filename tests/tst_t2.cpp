#include <QApplication>
#include <QSpinBox>
#include <catch2/catch_all.hpp>

#include "base.h"
#include "gameconfig.h"

constinit int fake_argc = 1;
char **fake_argv{};
QApplication app(fake_argc, fake_argv);

#include <QRadioButton>
#include <QLineEdit>

TEST_CASE("check gameConfig players names") {
    gameconfig g;
    g.setPlayer1Name("test1");
    g.setPlayer2Name("test2");

    REQUIRE(g.getPlayer1Name() == "test1");
    REQUIRE(g.getPlayer2Name() == "test2");
}

TEST_CASE("check maximum slide range") {
    gameconfig g;
    auto spin = g.findChild<QSpinBox *>("spinBox");
    REQUIRE(spin->maximum() == SideConfig::MAX_RANGE);
}


SCENARIO("check Ai mode configuration") {
    GIVEN("by default two player mode is selected ") {
    gameconfig g;
    auto ai_btn = g.findChild<QRadioButton*>("AiMode");
    auto twoPlayer_btn = g.findChild<QRadioButton*>("twoPlayerMode");
        REQUIRE(twoPlayer_btn->isChecked());

        WHEN("when we click on Ai btn some attributes will change") {
            ai_btn->clicked();

            THEN("lineEdit two text must be " + MetaData::AI_NAME.toStdString()) {
                auto lineEdit = g.findChild<QLineEdit*>("lineEdit2");
                REQUIRE(lineEdit->text() == MetaData::AI_NAME);
            }
        }
    }

}
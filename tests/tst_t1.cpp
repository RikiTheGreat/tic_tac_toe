#define CATCH_CONFIG_MAIN
#include <base.h>
#include <tictactoewidget.h>

#include <QApplication>
#include <catch2/catch_all.hpp>

// note: you must define Qpplication before QWidget
// ttt_widget is based on QWidget we have to create a useless Qapplication
//
constinit int fake_argc = 1;
char **fake_argv{};
QApplication app(fake_argc, fake_argv);

TEST_CASE("Check player setter and getter") {
    TicTacToeWidget tic;

    Player p{Player::player2};
    tic.setPlayer(p);
    REQUIRE(Player::player2 == tic.getPlayer());
}

TEST_CASE("check reset") {
    TicTacToeWidget tic;
    auto list = tic.getBoard();

    for (auto const &item : list) {
        if (!item->text().isEmpty())
            REQUIRE(false);
    }

    REQUIRE(true);
}

SCENARIO("side value can be changes", "[Side]") {
    GIVEN("Default value is 3") {
        TicTacToeWidget tic;
        REQUIRE(tic.getSide() == SideConfig::MIN_RANGE);

        WHEN("Changing side size to something else") {
            tic.setSide(5);

            THEN("side has a new value") {
                REQUIRE(tic.getSide() == 5);
            }
        }
    }
}

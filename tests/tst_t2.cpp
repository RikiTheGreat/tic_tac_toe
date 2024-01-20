#include <QApplication>
#include <QSpinBox>
#include <catch2/catch_all.hpp>

#include "base.h"
#include "gameconfig.h"

constinit int fake_argc = 1;
char **fake_argv{};
QApplication app(fake_argc, fake_argv);

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

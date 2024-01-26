#include <base.h>

#include <QApplication>
#include <QLabel>
#include <catch2/catch_all.hpp>

#include "mainwindow.h"

// constinit int fake_argc = 1;
// char **fake_argv{};
// QApplication app(fake_argc, fake_argv);

TEST_CASE("color of players' labels") {
    mainwindow m;
    auto p1_lbl = m.findChild<QLabel *>("p1_lbl");
    auto p2_lbl = m.findChild<QLabel *>("p2_lbl");

    REQUIRE(p1_lbl->styleSheet().contains(MetaData::PLAYER_1_COLOR));
    REQUIRE(p2_lbl->styleSheet().contains(MetaData::PLAYER_2_COLOR));
}
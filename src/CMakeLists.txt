set(lib_SRC
        tictactoewidget.cpp
        tictactoewidget.h
        base.h
        gameconfig.h gameconfig.cpp
        gameconfig.ui
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        logger.cpp
        logger.h
)
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()
add_library(ttt_lib ${lib_SRC})
target_link_libraries(ttt_lib PUBLIC Qt${QT_VERSION_MAJOR}::Widgets
                                        spdlog::spdlog
                                        ccache::ccache)

qt_add_executable(tictactoe main.cpp res.qrc
    )
# connect resources (images) to the project


target_link_libraries(tictactoe PUBLIC ttt_lib )

include(ClangFormat)
add_clangformat_target(format ${CMAKE_SOURCE_DIR})

# add_dependencies(tictactoe format)

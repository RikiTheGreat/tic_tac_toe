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
        openai.hpp
        ai.cpp
        ai.h
)
configure_file(${CMAKE_SOURCE_DIR}/PATH.h.in path.h @ONLY)

add_library(ttt_lib ${lib_SRC})
target_link_libraries(ttt_lib PUBLIC Qt${QT_VERSION_MAJOR}::Widgets
                                        spdlog::spdlog
                                        ccache::ccache
                                        CURL::libcurl nlohmann_json::nlohmann_json
)

target_include_directories(ttt_lib PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
if(MSVC)
    target_compile_options(ttt_lib PRIVATE /W4 /WX)
else()
    target_compile_options(ttt_lib PRIVATE -Wall -Wextra -Wpedantic )
endif()

qt_add_executable(tictactoe main.cpp res.qrc
    )

target_link_libraries(tictactoe PUBLIC ttt_lib )

if (DO_FORMAT)
    include(ClangFormat)
    add_clangformat_target(format ${CMAKE_SOURCE_DIR})
    add_dependencies(tictactoe format)
endif ()
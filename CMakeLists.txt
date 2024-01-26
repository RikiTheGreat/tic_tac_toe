cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_COMPILER_LAUNCHER "ccache")
project(tic_tac_toe VERSION 1.0 LANGUAGES CXX)
set(CMAKE_TOOLCHAIN_FILE conan_toolchain.cmake)


option(DO_TEST "enable testing" OFF)
option(DO_DOC "enable generating documentation" OFF)
option(DO_FORMAT "enable formatting" OFF)

if(DO_FORMAT)
# appending cmake path to cmake module in case of including my clang format module
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
endif ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(spdlog REQUIRED)
find_package(Doxygen REQUIRED doxygen)
find_package(ccache REQUIRED)
find_package(CURL)
find_package(nlohmann_json)

# helps promoted ui_* files recognize src/files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
# for PATH.h.in file
set(PATH_STRING ${CMAKE_SOURCE_DIR})

add_subdirectory(src)

if(DO_TEST)
    add_subdirectory(tests)
endif ()

if(DO_DOC)
    add_subdirectory(doc)
endif ()


cmake_minimum_required(VERSION 3.27)
project(tic_tac_toe VERSION 0.1 LANGUAGES CXX)
set(CMAKE_TOOLCHAIN_FILE conan_toolchain.cmake)
# appending cmake path to cmake module in case of including my clang format module
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER_LAUNCHER "ccache")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(spdlog REQUIRED)
find_package(Doxygen REQUIRED doxygen)
find_package(ccache REQUIRED)

# helps promoted ui_* files recognize src/files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(doc)

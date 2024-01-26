message("enable testing")
enable_testing()
include(CTest)

set(ALL_TESTS
        tst_t1.cpp
        tst_t2.cpp
        tst_t3.cpp
    )

set(F_NAME " ")
find_package(Catch2 CONFIG REQUIRED)

include_directories(../src)
add_executable(tttTest ${ALL_TESTS})
target_link_libraries(tttTest PRIVATE Catch2::Catch2 Catch2::Catch2WithMain ttt_lib)






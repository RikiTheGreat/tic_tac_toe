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
foreach(tst ${ALL_TESTS})
    get_filename_component(F_NAME ${tst} NAME_WLE)
    add_executable(${F_NAME} ${tst}

    )
    target_include_directories(${F_NAME} PRIVATE ../src)
    target_link_directories(${F_NAME} PRIVATE ../src)
    target_link_libraries(${F_NAME} PRIVATE Catch2::Catch2 Catch2::Catch2WithMain ttt_lib)
    add_test(tst_${F_NAME} ${F_NAME})

endforeach()






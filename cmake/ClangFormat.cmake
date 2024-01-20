function(add_clangformat_target TARGET_NAME SRC_DIR)
    find_program(CLANG_FORMAT_PATH clang-format REQUIRED)
    file(GLOB_RECURSE format_SRC
        LIST_DIRECTORIES false
            "${SRC_DIR}/*.cpp"
            "${SRC_DIR}/*.h"
    )

    #create a custom target to run clang-format
    add_custom_target(${TARGET_NAME}
    COMMAND ${CLANG_FORMAT_PATH} -i ${format_SRC} -style=file
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Running clang-format on ${format_SRC} files"
    )
endfunction()
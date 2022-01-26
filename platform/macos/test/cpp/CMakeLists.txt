
list(APPEND GAME_SOURCES_TEST
        ${${PROJECT_NAME}_SRCS_TEST}
        ${${PROJECT_NAME}_HDRS_TEST}
        )

add_executable( ${PROJECT_NAME}-test-static ${GAME_SOURCES_TEST} ${TARGET_RESOURCES})

list(APPEND INSTALL_LIBS ${PROJECT_NAME}-test-static)

target_link_libraries( ${PROJECT_NAME}-test-static ${PROJECT_NAME}-static gtest gmock_main)
target_compile_definitions(${PROJECT_NAME}-test-static PRIVATE ${${PROJECT_NAME}_DEFINITIONS})

add_test(NAME ${PROJECT_NAME}-test-static COMMAND ${PROJECT_NAME}-test-static)


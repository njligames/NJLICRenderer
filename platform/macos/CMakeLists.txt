list(APPEND ${PROJECT_NAME}_TARGET_LIBRARIES "-framework OpenGL")

if(${PROJECT_NAME}_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

add_library(${PROJECT_NAME}-static STATIC
        ${${PROJECT_NAME}_SRCS}
        ${${PROJECT_NAME}_HDRS}
        )
target_link_libraries(${PROJECT_NAME}-static ${${PROJECT_NAME}_TARGET_LIBRARIES})
target_include_directories(${PROJECT_NAME}-static PUBLIC ${${PROJECT_NAME}_PUBLIC_DIRECTORIES})
target_include_directories(${PROJECT_NAME}-static PRIVATE ${${PROJECT_NAME}_PRIVATE_DIRECTORIES})
target_compile_definitions(${PROJECT_NAME}-static PRIVATE ${${PROJECT_NAME}_DEFINITIONS})

list(APPEND INSTALL_LIBS ${PROJECT_NAME}-static)

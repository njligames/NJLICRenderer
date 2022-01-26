list(APPEND ${CMAKE_PROJECT_NAME}_TARGET_LIBRARIES "-framework OpenGL")

if(${CMAKE_PROJECT_NAME}_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

add_library(${CMAKE_PROJECT_NAME}-static STATIC
        ${${CMAKE_PROJECT_NAME}_SRCS}
        ${${CMAKE_PROJECT_NAME}_HDRS}
        )
target_link_libraries(${CMAKE_PROJECT_NAME}-static ${${CMAKE_PROJECT_NAME}_TARGET_LIBRARIES})
target_include_directories(${CMAKE_PROJECT_NAME}-static PUBLIC ${${CMAKE_PROJECT_NAME}_PUBLIC_DIRECTORIES})
target_include_directories(${CMAKE_PROJECT_NAME}-static PRIVATE ${${CMAKE_PROJECT_NAME}_PRIVATE_DIRECTORIES})
target_compile_definitions(${CMAKE_PROJECT_NAME}-static PRIVATE ${${CMAKE_PROJECT_NAME}_DEFINITIONS})

list(APPEND INSTALL_LIBS ${PROJECT_NAME}-static)

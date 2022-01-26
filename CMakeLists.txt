cmake_minimum_required(VERSION 3.17)
project(NJLICRenderer)

set(CMAKE_CXX_STANDARD 14)

# The following variables are used to build the targets.
# ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS
# ${CMAKE_PROJECT_NAME}_PUBLIC_DIRECTORIES
# ${CMAKE_PROJECT_NAME}_PRIVATE_DIRECTORIES
# ${CMAKE_PROJECT_NAME}_TARGET_LIBRARIES
# ${CMAKE_PROJECT_NAME}_DEFINITIONS
# ${CMAKE_PROJECT_NAME}_SRCS
# ${CMAKE_PROJECT_NAME}_HDRS
# ${CMAKE_PROJECT_NAME}_SRCS_TEST
# ${CMAKE_PROJECT_NAME}_HDRS_TEST

include(cmake/configure.cmake)

configure_file(cmake/glm.cmake.in glm-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glm-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glm-download )
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/glm-src ${CMAKE_CURRENT_BINARY_DIR}/glm-build)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/glm-src)
list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS ${GLM_INCLUDE_DIR})

configure_file(cmake/nlohmann_json.cmake.in nlohmann_json-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-download )
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-src ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-build)
set(NLOHMANN_JSON_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-src/include)
list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS ${NLOHMANN_JSON_INCLUDE_DIR})

if(NOT TARGET SDL2-static OR
        NOT TARGET SDL2main OR
        NOT TARGET SDL2)
    # Download and unpack SDL2 at configure time
    configure_file(cmake/sdl.cmake.in sdl-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sdl-download )
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sdl-download )
    # Add SDL2 directly to our build. This adds the following targets: SDL2-static SDL2main SDL2
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/sdl-src ${CMAKE_CURRENT_BINARY_DIR}/sdl-build)
    list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS ${SDL_INCLUDE_DIR})
endif()

list(APPEND ${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/thirdparty)

list(APPEND ${CMAKE_PROJECT_NAME}_TARGET_LIBRARIES
        SDL2
        )

list(APPEND ${CMAKE_PROJECT_NAME}_PUBLIC_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/platform/macos
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${${CMAKE_PROJECT_NAME}_THIRDPARTY_INCLUDE_DIRS}
        )

list(APPEND ${CMAKE_PROJECT_NAME}_PRIVATE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

list(APPEND ${CMAKE_PROJECT_NAME}_DEFINITIONS __GL_2__=1)

list(APPEND ${CMAKE_PROJECT_NAME}_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Util.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Geometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/MaterialProperty.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/MeshGeometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/SpriteGeometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Scene.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/SphereGeometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/BackgroundRenderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DebugDrawer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/PubSub.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/BitmapFont.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Camera2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Color.cpp
        )

list(APPEND ${CMAKE_PROJECT_NAME}_HDRS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Util.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Shader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Geometry.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/MaterialProperty.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Node.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/MeshGeometry.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/SpriteGeometry.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Scene.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/SphereGeometry.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/BackgroundRenderer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/DebugDrawer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/PubSub.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/BitmapFont.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Camera2.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Color.h
        )

list(APPEND ${CMAKE_PROJECT_NAME}_SRCS_TEST ${CMAKE_CURRENT_SOURCE_DIR}/test/TestRender.cpp)
list(APPEND ${CMAKE_PROJECT_NAME}_HDRS_TEST ${CMAKE_CURRENT_SOURCE_DIR}/test/TestRender.h)
list(APPEND ${CMAKE_PROJECT_NAME}_SRCS_TEST ${CMAKE_CURRENT_SOURCE_DIR}/test/TestColor.cpp)
list(APPEND ${CMAKE_PROJECT_NAME}_HDRS_TEST ${CMAKE_CURRENT_SOURCE_DIR}/test/TestColor.h)


# Download and unpack googletest at configure time
configure_file(cmake/googletest.cmake.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build)

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif()

add_subdirectory(${PLATFORM_DIR})

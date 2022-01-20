cmake_minimum_required(VERSION 3.17)
project(NJLICRenderer)

set(CMAKE_CXX_STANDARD 14)


configure_file(nlohmann_json.cmake.in nlohmann_json-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-download )
# Add SDL2 directly to our build. This adds the following targets: SDL2-static SDL2main SDL2
add_subdirectory(${CMAKE_BINARY_DIR}/nlohmann_json-src ${CMAKE_BINARY_DIR}/nlohmann_json-build)
set(NLOHMANN_JSON_INCLUDE_DIR ${CMAKE_BINARY_DIR}/nlohmann_json-src/include)
list(APPEND THIRDPARTY_INCLUDE_DIRS ${NLOHMANN_JSON_INCLUDE_DIR})


if(NOT TARGET SDL2-static OR
        NOT TARGET SDL2main OR
        NOT TARGET SDL2)
    # Download and unpack SDL2 at configure time
    configure_file(sdl.cmake.in sdl-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sdl-download )
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sdl-download )
    # Add SDL2 directly to our build. This adds the following targets: SDL2-static SDL2main SDL2
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/sdl-src ${CMAKE_CURRENT_BINARY_DIR}/sdl-build)
    list(APPEND THIRDPARTY_INCLUDE_DIRS ${SDL_INCLUDE_DIR})
endif()

add_library(NJLICRenderer
        library.cpp
        Util.cpp
        Shader.cpp
        Geometry.cpp
        MaterialProperty.cpp
        Camera.cpp
        Node.cpp
        MeshGeometry.cpp
        SpriteGeometry.cpp
        Scene.cpp
        SphereGeometry.cpp
        BackgroundRenderer.cpp
        DebugDrawer.cpp
        PubSub.cpp
        BitmapFont.cpp
        Camera2.cpp
        )
target_compile_definitions(NJLICRenderer PUBLIC __GL_2__=1)
target_include_directories(NJLICRenderer PUBLIC "platform/macos" "include")
target_include_directories(NJLICRenderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(NJLICRenderer
        SDL2
        )
target_include_directories(NJLICRenderer
        PUBLIC
        ${THIRDPARTY_INCLUDE_DIRS}
        )


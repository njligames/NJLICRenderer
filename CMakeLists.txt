cmake_minimum_required(VERSION 3.17)
project(NJLICRenderer)

set(CMAKE_CXX_STANDARD 14)

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

add_library(NJLICRenderer library.cpp Util.cpp Shader.cpp Geometry.cpp MaterialProperty.cpp Camera.cpp Node.cpp MeshGeometry.cpp SpriteGeometry.cpp Scene.cpp SphereGeometry.cpp)
target_compile_definitions(NJLICRenderer PUBLIC __GL_2__=1)
target_include_directories(NJLICRenderer PUBLIC "platform/macos" "include")
target_include_directories(NJLICRenderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(NJLICRenderer
        SDL2
        )
target_include_directories(NJLICRenderer
        PUBLIC
        ${SDL_INCLUDE_DIR}
        )


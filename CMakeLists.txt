cmake_minimum_required(VERSION 3.21)
project(NJLICRenderer)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

add_library(NJLICRenderer library.cpp Util.cpp Shader.cpp Geometry.cpp MaterialProperty.cpp Camera.cpp Node.cpp MeshGeometry.cpp SpriteGeometry.cpp Scene.cpp SphereGeometry.cpp)
target_compile_definitions(NJLICRenderer PUBLIC __GL_2__=1)
target_include_directories(NJLICRenderer PUBLIC "platform/macos" "include")
target_include_directories(NJLICRenderer PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(NJLICRenderer
        ${SDL2_LIBRARIES}
        )
target_include_directories(NJLICRenderer
        PUBLIC
        ${SDL2_INCLUDE_DIRS}
        )


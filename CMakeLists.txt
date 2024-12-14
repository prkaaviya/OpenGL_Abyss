cmake_minimum_required(VERSION 3.29)
project(try8)

set(CMAKE_CXX_STANDARD 17)

add_library(glad ${PROJECT_SOURCE_DIR}/Dependencies/glad/src/glad.c)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/include/gl)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glm/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/include/assimp)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp REQUIRED)

add_executable(try8 main.cpp
        Mesh.cpp
        Mesh.h
        Window.cpp
        Window.h
        Shader.cpp
        Shader.h)

target_link_libraries(try8 PRIVATE glad)
target_link_libraries(try8 PRIVATE /Users/prkaaviya/CLionProjects/try8/Dependencies/lib/GL/libGLEW.dylib)
target_link_libraries(try8 PRIVATE assimp::assimp)
target_link_libraries(try8 PRIVATE glfw)
target_link_libraries(try8 PRIVATE glm::glm)
target_link_libraries(try8 PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
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
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp REQUIRED)

add_executable(try8 main.cpp
        Camera.cpp
        Camera.h
        CommonValues.h
        DirectionalLight.cpp
        DirectionalLight.h
        FishMovement.cpp
        FishMovement.h
        Light.cpp
        Light.h
        Material.cpp
        Material.h
        Mesh.cpp
        Mesh.h
        Model.cpp
        Model.h
        PointLight.cpp
        PointLight.h
        Shader.cpp
        Shader.h
        Skybox.cpp
        Skybox.h
        SpotLight.cpp
        SpotLight.h
        stb_image.h
        Texture.cpp
        Texture.h
        Window.cpp
        Window.h
        OBJLoader.cpp
        OBJLoader.h
        StarfishMovement.h
        CoralAnimator.h
)

target_link_libraries(try8 PRIVATE glad)
target_link_libraries(try8 PRIVATE /Users/prkaaviya/CLionProjects/try8/Dependencies/lib/GL/libGLEW.dylib)
target_link_libraries(try8 PRIVATE assimp::assimp)
target_link_libraries(try8 PRIVATE glfw)
target_link_libraries(try8 PRIVATE glm::glm)
target_link_libraries(try8 PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
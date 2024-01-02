cmake_minimum_required(VERSION 3.23)

project(phaba-playground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(phaba-playground Main.cpp "Application/Application.cpp" "Renderer/Renderer.cpp" "Renderer/Shaders/Shaders.h" "Shape/Shape.cpp" "Renderer/Colors/Colors.hpp" "Renderer/Colors/Colors.cpp"  "GenericScene/GenericScene.cpp" "Object/Object.hpp" "Scenes/Demo1/Demo1.cpp")

find_package(SDL2)
find_package(glew)
find_package(glm)

target_include_directories(phaba-playground PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(phaba-playground PRIVATE SDL2::SDL2-static GLEW::GLEW glm::glm phaba-gl phaba)

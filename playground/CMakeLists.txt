cmake_minimum_required(VERSION 3.23)

project(phaba-playground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(phaba-playground Main.cpp "Application/Application.cpp")

find_package(SDL2)
find_package(glew)

target_link_libraries(phaba-playground PRIVATE SDL2::SDL2-static GLEW::GLEW)

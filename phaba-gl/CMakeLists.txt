cmake_minimum_required(VERSION 3.23)

project(phaba-gl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(phaba-gl "Shader/Shader.cpp" "Shader/Shader.hpp" "Program/Program.cpp" "Buffer/Buffer.cpp")

find_package(glew)

target_include_directories(phaba-gl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(phaba-gl PUBLIC GLEW::GLEW)

cmake_minimum_required(VERSION 3.23)

project(phaba LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(phaba "World/World.cpp" "World/World.hpp" "Body/Body.cpp" "World/Detail/Engine.cpp" "BodyPart/BodyPart.cpp" "World/Detail/Bodies/Bodies.cpp")

find_package(glew)
find_package(glm)

target_include_directories(phaba PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(phaba PUBLIC GLEW::GLEW glm::glm phaba-gl)

cmake_minimum_required(VERSION 3.23)

project(phaba LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(playground)
add_subdirectory(phaba-gl)
add_subdirectory(src)
add_subdirectory(test)

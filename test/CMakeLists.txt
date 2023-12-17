cmake_minimum_required(VERSION 3.23)

project(phaba-test LANGUAGES CXX)

add_executable(phaba-test Main.cpp "WorldTest.cpp")

find_package(GTest REQUIRED)
find_package(SDL2 REQUIRED)

target_link_libraries(phaba-test PRIVATE GTest::GTest phaba SDL2::SDL2-static)
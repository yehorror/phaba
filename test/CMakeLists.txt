cmake_minimum_required(VERSION 3.23)

project(phaba-test LANGUAGES CXX)

add_executable(phaba-test Main.cpp)

find_package(GTest REQUIRED)

target_link_libraries(phaba-test PRIVATE GTest::GTest)
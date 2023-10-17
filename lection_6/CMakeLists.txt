cmake_minimum_required(VERSION 3.0)

project(RedBlackTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(RedBlackTree main.cpp)

target_compile_features(RedBlackTree PRIVATE cxx_nullptr)

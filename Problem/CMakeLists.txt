cmake_minimum_required(VERSION 3.17)
project(Problem)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Problem
        src/FileHandler.cpp
        src/FileHandler.hpp
        src/Problem.cpp
        src/Problem.hpp
        tests/main.cpp)

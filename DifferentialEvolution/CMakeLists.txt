cmake_minimum_required(VERSION 3.17)
project(DifferentialEvolution)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(DifferentialEvolution
        src/DifferentialEvolution.cpp
        src/DifferentialEvolution.hpp
        src/FileHandler.cpp
        src/FileHandler.hpp
        tests/main.cpp)

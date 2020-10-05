cmake_minimum_required(VERSION 3.17)
project(LocalSearch)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(LocalSearch
        src/FileHandler.cpp
        src/FileHandler.hpp
        src/LocalSearch.cpp
        src/LocalSearch.hpp
        tests/main.cpp)

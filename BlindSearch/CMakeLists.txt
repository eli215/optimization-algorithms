cmake_minimum_required(VERSION 3.17)
project(BlindSearch)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(BlindSearch
        src/BlindSearch.cpp
        src/BlindSearch.h
        src/FileHandler.cpp
        src/FileHandler.h
        tests/main.cpp)

cmake_minimum_required(VERSION 3.17)
project(NEH)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(NEH
        src/FileHandler.cpp
        src/FileHandler.h
        src/NEH.cpp
        src/NEH.h
        tests/main.cpp)

cmake_minimum_required(VERSION 3.27)
project(SO2_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(SO2_1 main.cpp
        Philosopher.cpp
        Philosopher.hpp)

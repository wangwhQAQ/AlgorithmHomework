cmake_minimum_required(VERSION 3.21)
project(shorestPath)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(shorestPath main.cpp)

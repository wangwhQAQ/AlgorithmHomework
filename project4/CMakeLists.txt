cmake_minimum_required(VERSION 3.21)
project(project4)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(project4 main.cpp)

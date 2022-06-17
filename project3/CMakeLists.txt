cmake_minimum_required(VERSION 3.21)
project(project3)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(project3 main.cpp)

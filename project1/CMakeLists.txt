cmake_minimum_required(VERSION 3.21)
project(project1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(project1 main.cpp)

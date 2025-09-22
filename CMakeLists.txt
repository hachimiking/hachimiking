cmake_minimum_required(VERSION 4.0)
project(hachimiking)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(hachimiking
        3123002977/work.cpp
        3123002977/最小编辑距离dp.cpp)

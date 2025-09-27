cmake_minimum_required(VERSION 4.0)
project(Assignment1_comp345)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment1_comp345
        Map.cpp
        Map.h
        MapDriver.cpp
)

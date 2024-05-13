cmake_minimum_required(VERSION 3.27)
project(MS2)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(MS2
        ms2.cpp
        Station.cpp
        Station.h
        Utilities.cpp
        Utilities.h
        CustomerOrder.cpp
        CustomerOrder.h)

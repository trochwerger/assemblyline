cmake_minimum_required(VERSION 3.27)
project(MS3)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(MS3
        CustomerOrder.cpp
        CustomerOrder.h
        ms3.cpp
        Station.cpp
        Station.h
        Utilities.cpp
        Utilities.h
        Workstation.cpp
        Workstation.h
        LineManager.cpp
        LineManager.h)

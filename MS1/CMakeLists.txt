cmake_minimum_required(VERSION 3.27)
project(MS1)

set(CMAKE_CXX_STANDARD 14)

add_executable(MS1
        ms1.cpp
        Stations1.txt
        Stations2.txt
        Utilities.cpp
        Station.cpp)

cmake_minimum_required(VERSION 3.23)
project(QuadTree)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(SOURCE_FILES
        source/main.cpp
        include/QuadTree.h
        source/QuadTree.cpp
        include/Geometry2D.h
        source/Geometry2D.cpp)

add_executable(QuadTree ${SOURCE_FILES})

cmake_minimum_required(VERSION 3.23)
project(QuadTree)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(QuadTree
        include/Geometry2D.h
        include/QuadTree2D.h
        source/Example.cpp
)
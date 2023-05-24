cmake_minimum_required(VERSION 3.22)
project(newstuff)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(AVL)

add_executable(newstuff
        AVL/AVL.h
        AVL/Node.h
        AVL/testing_avl.cpp
        Array.h
        Group.cpp
        Group.h
        macros.h
        maina1.cpp
        Movie.cpp
        Movie.h
        StreamingDBa1.cpp
        StreamingDBa1.h
        User.cpp
        User.h
        wet1util.h)

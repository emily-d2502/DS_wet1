cmake_minimum_required(VERSION 3.22)
project(DS)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Array)
include_directories(AVL)

add_executable(temp
        Array/Array.h
        AVL/AVL.h
        AVL/class_defines.h
        AVL/Node.h
        AVL/testing.cpp
        Group.h
        macros.h
        main.cpp
        maina1.cpp
        Movie.h
        StreamingDBa1.cpp
        StreamingDBa1.h
        User.h
        wet1util.h)

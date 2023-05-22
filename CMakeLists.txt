cmake_minimum_required(VERSION 3.22)
project(DS_cur)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(AVL)
include_directories(Classes)

add_executable(DS_cur
        AVL/AVL.h
        AVL/Node.h
        AVL/testing_avl.cpp
        Classes/Group.cpp
        Classes/Group.h
        Classes/Movie.cpp
        Classes/Movie.h
        Classes/User.cpp
        Classes/User.h
        Array.h
        macros.h
        maina1.cpp
        StreamingDBa1.cpp
        StreamingDBa1.h
        wet1util.h)

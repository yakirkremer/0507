cmake_minimum_required(VERSION 2.8.12.2)
project(__1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(__1
        AvlTree.h
        maina1.cpp
        StreamingDBa1.cpp
        StreamingDBa1.h
        wet1util.h main.cpp User.h Movie.h Comperator.h Group.h Movies.h AvlTreeNew.h)

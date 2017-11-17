cmake_minimum_required(VERSION 3.0)
project(GSkyline_6)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES
        experiment.cpp
        GGroup.cpp
        GGroup.h
        GPoint.cpp
        GPoint.h
        GSkyline.cpp
        GSkyline.h
        main.cpp
        PointWisePlus.cpp
        PointWisePlus.h
        UnitGroup.cpp
        UnitGroup.h
        UnitWisePlus.cpp
        UnitWisePlus.h PointWise.cpp PointWise.h)

add_executable(GSkyline_6 ${SOURCE_FILES})
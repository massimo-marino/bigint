cmake_minimum_required(VERSION 3.26)

#set(CMAKE_CXX_COMPILER "/usr/bin/g++")
SET(CMAKE_BUILD_TYPE Release) # Debug, Release, RelWithDebInfo, MinSizeRel

PROJECT(bigint-lib)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(src/unitTests)
ADD_SUBDIRECTORY(src/fibonacci)
ADD_SUBDIRECTORY(src/fibonacci/fibmemo)


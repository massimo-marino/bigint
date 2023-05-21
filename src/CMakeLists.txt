#
SET(THE_PROJECT libbigint)

cmake_minimum_required(VERSION 3.26)

PROJECT(${THE_PROJECT} VERSION 1.0.0 DESCRIPTION "libbigint: a lib for big integers")

SET(LIBRARY_NAME bigint)

# C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_EXPORT_COMPILE_COMMANDS on)

SET(CMAKE_VERBOSE_MAKEFILE on)
SET(BUILD_SHARED_LIBS ON)

# Set the variable source_files to the list of names of your C++ source code
SET(SOURCE_FILES
   bigint.cpp
)

#SET(CMAKE_BUILD_TYPE Debug) # Debug, Release, RelWithDebInfo, MinSizeRel

# Set the build type (Debug or Release)
if(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
endif()

# Set more compiler flags for debug mode; -g is automatically set
if(CMAKE_BUILD_TYPE MATCHES Debug)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Set more compiler flags for release mode; -O3 is automatically set
if(CMAKE_BUILD_TYPE MATCHES Release)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
endif()

#ADD_LIBRARY(${LIBRARY_NAME} STATIC ${SOURCE_FILES})
ADD_LIBRARY(${LIBRARY_NAME} ${SOURCE_FILES}) # shared lib

SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES SOVERSION 1)
SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER bigint.h)

TARGET_INCLUDE_DIRECTORIES(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


#
SET(THE_PROJECT fibmemo)

cmake_minimum_required(VERSION 3.26)

PROJECT(${THE_PROJECT} VERSION 1.0.0 DESCRIPTION "fibonacci with memoization example with bigint's")

# C++ version
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_VERBOSE_MAKEFILE ON)

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

# Set the variable source_files to the list of names of your C++ source code
# Note the lack of commas or other deliminators
SET(SOURCE_FILES
   fibmemo.cpp
)

# Build a program called '${THE_PROJECT}' from the source files we specified above
ADD_EXECUTABLE(${THE_PROJECT} ${SOURCE_FILES})

FIND_PACKAGE(Boost REQUIRED COMPONENTS program_options filesystem system)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
#    TARGET_LINK_LIBRARIES(${OBJ_EXECUTABLE} LINK_PUBLIC bigint ${Boost_LIBRARIES})
ENDIF()

SET(LINKED_LIBS bigint)
TARGET_LINK_LIBRARIES(${THE_PROJECT} LINK_PUBLIC ${LINKED_LIBS} ${Boost_LIBRARIES})


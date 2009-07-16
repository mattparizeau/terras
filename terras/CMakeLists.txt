# CMake list file for terras
cmake_minimum_required (VERSION 2.6)
project (terras)

#SET(CMAKE_VERBOSE_MAKEFILE ON)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "-g -pg -Wall -pedantic -Wextra -Wno-long-long")
endif(CMAKE_COMPILER_IS_GNUCC)

set(TERRAS_VERSION_MAJOR "0")
set(TERRAS_VERSION_MINOR "0")
set(TERRAS_VERSION_PATCH "0")
set(TERRAS_VERSION_BUILD "1")
set(TERRAS_VERSION "${TERRAS_VERSION_MAJOR}.${TERRAS_VERSION_MINOR}.${TERRAS_VERSION_PATCH}-${TERRAS_VERSION_BUILD}")

FILE(GLOB public_headers include/*.h)
FILE(GLOB private_headers src/*.h)
FILE(GLOB sources src/*.cpp)

ADD_EXECUTABLE (terras ${sources})

FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs)

INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
LINK_DIRECTORIES (${PYTHON_LIB_PATH}) 
#INCLUDE_DIRECTORIES("/usr/local/include")
#ADD_LIBRARY(terras python)

# Link the executable to the Hello library.
target_link_libraries (terras python2.6) 

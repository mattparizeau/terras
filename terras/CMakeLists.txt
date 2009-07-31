# CMake list file for terras
cmake_minimum_required (VERSION 2.6)
project (terras)

#SET(CMAKE_VERBOSE_MAKEFILE ON)
#SET(DEBUG ON)

if(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS "-g -pg -Wall -pedantic -Wextra -Wno-long-long")
endif(CMAKE_COMPILER_IS_GNUCC)



set(TERRAS_VERSION_MAJOR "0")
set(TERRAS_VERSION_MINOR "0")
set(TERRAS_VERSION_PATCH "1")
set(TERRAS_VERSION_BUILD "1")
set(TERRAS_VERSION "${TERRAS_VERSION_MAJOR}.${TERRAS_VERSION_MINOR}.${TERRAS_VERSION_PATCH}-${TERRAS_VERSION_BUILD}")

FILE(GLOB public_headers include/*.h)
FILE(GLOB private_headers src/*.h)
FILE(GLOB sources src/*.cpp)

add_subdirectory(libs/yaml-cpp)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH} ${BOOST_INCLUDE_PATH} ${SDL_INCLUDE_PATH})
LINK_DIRECTORIES (${PYTHON_LIB_PATH} ${BOOST_LIB_PATH} ${SDL_LIB_PATH}) 

ADD_EXECUTABLE (terras ${sources})
#ADD_LIBRARY (pyterras ${pythonSources})

# Packages we link to
FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs)
FIND_PACKAGE(Boost)
FIND_PACKAGE(SDL)

# link to the appropriate libraries
target_link_libraries (terras yaml-cpp python2.6 boost_python SDL)
#target_link_libraries (pyterras python2.6 boost_python) 

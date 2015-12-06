cmake_minimum_required(VERSION 3.3)
project(Compresseur)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES dpcm.cpp)
add_executable(Compresseur ${SOURCE_FILES})
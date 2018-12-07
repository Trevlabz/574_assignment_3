# CMakeList.txt : CMake project for hlsyn, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.2)


if(MSVC)
    set( CMAKE_CXX_FLAGS "-W4" )
    set(CMAKE_DEBUG_POSTFIX "d")
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
else()
    add_definitions(-Wall -g)
    link_libraries(m)
endif()

set(CMAKE_CXX_FLAGS "-std=c++11")

file( GLOB SRCS *.cpp *.h )

add_executable (hlsyn "hlsyn.cpp" "hlsyn.h" "general.h" "general.cpp" "node.h" "node.cpp")

# CMakeList.txt : CMake project for hlsyn, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (hlsyn "hlsyn.cpp" "hlsyn.h" "general.h" "general.cpp" "node.h" "node.cpp")

# TODO: Add tests and install targets if needed.

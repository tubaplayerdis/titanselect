cmake_minimum_required(VERSION 3.15)
project(titanselect C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Add all source directories
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "include/*.h" "include/*.hpp")

add_executable(titanselect ${SOURCES})
cmake_minimum_required(VERSION 3.5)
project(DijkstraShortestPath LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(library)
add_subdirectory(program)
add_subdirectory(testrunner)

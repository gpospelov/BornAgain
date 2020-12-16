cmake_minimum_required(VERSION 3.14)
project(DaRefl VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(DAREFL_BUMP_VERSION "Propagate version number" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/modules)
include(configuration)

add_subdirectory(source)
add_subdirectory(tests)

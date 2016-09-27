cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(CylindersAndPrisms)

add_executable(CylindersAndPrisms CylindersAndPrisms.cpp)

# path to the cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)

# find libraries
find_package(BornAgain REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${BORNAGAIN_INCLUDE_DIR}
)

target_link_libraries(CylindersAndPrisms
    ${BORNAGAIN_LIBRARIES}
)

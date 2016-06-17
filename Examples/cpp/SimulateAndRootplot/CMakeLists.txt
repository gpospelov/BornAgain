cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(CylindersAndPrisms)

add_executable(CylindersAndPrisms CylindersAndPrisms.cpp)

# path to the cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)

# Find libraries

# --- Eigen3 ---
find_package(Eigen3 3.1.0 REQUIRED)

# --- BOOST ---
set(boost_libraries_required date_time chrono program_options iostreams system filesystem regex thread)
find_package(Boost 1.48.0 COMPONENTS ${boost_libraries_required} REQUIRED)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

# --- BornAgain ---
find_package(BornAgain REQUIRED)

#-----ROOT------------
find_package(ROOT REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${ROOT_INCLUDE_DIR}
    ${BORNAGAIN_INCLUDE_DIR}
)

target_link_libraries(CylindersAndPrisms
    ${Boost_LIBRARIES}
    ${BORNAGAIN_LIBRARIES}
    ${ROOT_LIBRARIES}
)

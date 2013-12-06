cmake_minimum_required(VERSION 2.8)
 
project(CylindersAndPrisms)

add_executable(CylindersAndPrisms CylindersAndPrisms.cpp)

set (CMAKE_CXX_FLAGS "-H -Wall")

# path to the cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)

# Find libraries

# --- Eigen3 ---
find_package(Eigen3 3.1.0)

# --- BOOST ---
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
#add_definitions(-DBOOST_ALL_DYN_LINK) # line is needed for MSVC

set(boost_libraries_required date_time chrono program_options iostreams system filesystem regex thread)

find_package(Boost 1.48.0 COMPONENTS ${boost_libraries_required} REQUIRED)

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

#-------BornAgain----------------
find_package(BornAgain)

#-----ROOT------------
find_package(ROOT)


include_directories(
    ${BA_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIR}
    ${EIGEN3_INCLUDE_DIR}
)

target_link_libraries(CylindersAndPrisms
    ${BA_LIBRARY}
    ${Boost_LIBRARIES}
    ${ROOT_LIBRARIES}
)



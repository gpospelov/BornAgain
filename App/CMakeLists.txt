############################################################################
# CMakeLists.txt file for building BornAgain/App executable
############################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(executable_name App)

# source files
file(GLOB source_files
    "src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS06/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS07/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS08/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS10/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS11/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS15/*.cpp"
)

# to get rid from files generated via qmake compilation
list(REMOVE_ITEM source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/AppDict.cpp)

# header files
file(GLOB include_files
    "inc/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS06/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS07/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS08/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS10/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS11/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS15/*.h"
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS06
    ${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS07
    ${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS08
    ${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS10
    ${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS11
    ${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS15
)

# data files are required by App for comparison
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Tests/ReferenceData/IsGISAXS ${CMAKE_BINARY_DIR}/Tests/ReferenceData/IsGISAXS)

# dictionaries
ROOT_GENERATE_DICTIONARY(AppDict    inc/DrawHelper.h inc/TreeEventStructure.h  LINKDEF AppLinkDef.h)

add_executable(${executable_name} ${source_files} AppDict.cxx ${header_files})

# dependencies
include_directories(${BornAgainCore_INCLUDE_DIRS})
target_link_libraries(${executable_name} ${BornAgainCore_LIBRARY}) 
include_directories(${BornAgainFit_INCLUDE_DIRS})
target_link_libraries(${executable_name} ${BornAgainFit_LIBRARY}) 

message("XXX ROOT_LIBRARIES ${ROOT_LIBRARIES}")
message("XXX ROOT_INCLUDE_DIR ${ROOT_INCLUDE_DIR}")
include_directories(${ROOT_INCLUDE_DIR})
target_link_libraries(${executable_name} ${ROOT_LIBRARIES}) 

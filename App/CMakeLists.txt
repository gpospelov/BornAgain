############################################################################
# CMakeLists.txt file for building BornAgain/App executalbe
############################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(executable_name App)

# files to have in library
file(GLOB source_files
    "src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS06/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS07/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS08/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS10/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS11/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Tests/FunctionalTests/TestCore/IsGISAXS15/*.cpp"
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



#dictionaries
ROOT_GENERATE_DICTIONARY(AppDict    inc/DrawHelper.h inc/TreeEventStructure.h  LINKDEF AppLinkDef.h)

add_executable(${executable_name} ${source_files} AppDict.cxx)


# dependencies
include_directories(${BornAgainCore_INCLUDE_DIRS})
target_link_libraries(${executable_name} ${BornAgainCore_LIBRARY}) 

message("AAA ${BornAgainFit_INCLUDE_DIRS}")
include_directories(${BornAgainFit_INCLUDE_DIRS})
target_link_libraries(${executable_name} ${BornAgainFit_LIBRARY}) 

target_link_libraries(${executable_name} ${ROOT_LIBRARIES}) 


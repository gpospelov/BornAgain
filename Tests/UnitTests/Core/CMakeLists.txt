############################################################################
# CMakeLists.txt file for building and running unit tests
############################################################################

enable_testing()

file(GLOB include_files "*.h")

add_executable( TestCore main.cpp ${include_files})

# dependencies
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(TestCore gtest)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
)
target_link_libraries(TestCore
    ${BornAgainCore_LIBRARY}
    ${Boost_LIBRARIES}
    ${GSL_LIBRARIES}
)

if(BORNAGAIN_OPENMPI)
    include_directories(${MPI_INCLUDE_PATH})
    target_link_libraries(TestCore ${MPI_LIBRARIES})
endif()


# to build executable right in lib directory to not to have problems with finding libBornAgainCore.dll under Windows
set_property(TARGET TestCore PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_test( TestCore TestCore) # TestName ExeName

# add execution of TestCore just after compilation
add_custom_command(TARGET TestCore POST_BUILD COMMAND TestCore)




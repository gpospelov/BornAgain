############################################################################
# CMakeLists.txt file for building and running unit tests
############################################################################

include(AddGTest)

# qtcreator prefers relative paths for project includes
include_directories(
    ../utilities
    ${BornAgainCore_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
    ${gtest_SOURCE_DIR}
    ${gtest_SOURCE_DIR}/include
    )
if(BORNAGAIN_OPENMPI)
    include_directories(${MPI_INCLUDE_PATH})
endif()

set(libs BornAgainCore)

ADD_GTEST(Core "0"        ${libs} 0)
ADD_GTEST(Core "1"        ${libs} 0)
ADD_GTEST(Core "2"        ${libs} 0)
ADD_GTEST(Core "3"        ${libs} 0)
ADD_GTEST(Core "4"        ${libs} 0)
ADD_GTEST(Core "5"        ${libs} 0)
ADD_GTEST(Core "6"        ${libs} 0)
ADD_GTEST(Core "Numeric0" ${libs} 1)
ADD_GTEST(Core "Numeric1" ${libs} 1)

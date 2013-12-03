############################################################################
# CMakeLists.txt file for building TestCore functional tests
############################################################################

set(CMAKE_CXX_FLAGS "-DSTANDALONE")

set(list_of_tests
    "IsGISAXS01"
    "IsGISAXS02"
    "IsGISAXS03BA"
    "IsGISAXS03DWBA"
    "IsGISAXS03BAsize"
    "IsGISAXS041DDL"
    "IsGISAXS042DDL"
    "IsGISAXS06L1"
    "IsGISAXS06L2"
    "IsGISAXS06L3"
    "IsGISAXS06L4"
    "IsGISAXS07"
    "IsGISAXS082DDL"
    "IsGISAXS082DDL2"
    "IsGISAXS09"
    "IsGISAXS10"
    "IsGISAXS11"
    "IsGISAXS15"
    "FormFactors"
    "MesoCrystal1"
    "PolarizedDWBAZeroMag"
)

# for some reason these flags doesn't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

foreach(_test ${list_of_tests})
   BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY})
   BORNAGAIN_ADD_TEST(${_test} INPUT_DIR ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/)
endforeach()



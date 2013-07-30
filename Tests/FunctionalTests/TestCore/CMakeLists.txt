############################################################################
# CMakeLists.txt file for building TestCore functional tests
############################################################################

set(CMAKE_CXX_FLAGS "-DSTANDALONE")

set(list_of_tests
    "IsGISAXS01"
    "IsGISAXS02"
    "IsGISAXS03"
    "IsGISAXS04"
    "IsGISAXS06"
    "IsGISAXS07"
    "IsGISAXS08"
    "IsGISAXS09"
    "IsGISAXS10"
    "IsGISAXS11"
    "IsGISAXS15"
#    "MesoCrystal1"
)

foreach(_test ${list_of_tests})
    BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY})
    BORNAGAIN_ADD_TEST(${_test} INPUT_DIR ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/)
endforeach()


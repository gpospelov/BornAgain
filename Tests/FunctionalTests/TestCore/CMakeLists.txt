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

include_directories(${Boost_INCLUDE_DIRS})
#link_directories(${CMAKE_BINARY_DIR}/lib)

foreach(_test ${list_of_tests})
    BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY})
    # to have executable in lib directory
    #set_property(TARGET ${_test} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    #BORNAGAIN_ADD_TEST(${CMAKE_BINARY_DIR}/lib/${_test} INPUT_DIR ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/)
    set_property(TARGET ${_test} PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
    BORNAGAIN_ADD_TEST(${_test} INPUT_DIR ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/)
endforeach()


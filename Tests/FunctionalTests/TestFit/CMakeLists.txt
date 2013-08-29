############################################################################
# CMakeLists.txt file for building TestFit functional tests
############################################################################

set(CMAKE_CXX_FLAGS "-DSTANDALONE")

set(list_of_tests
    "TestFit01"
    "TestFit02"
)

include_directories(${Boost_INCLUDE_DIRS})

foreach(_test ${list_of_tests})
    BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY} ${BornAgainFit_LIBRARY})
    # to have executable in lib directory
    set_property(TARGET ${_test} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    BORNAGAIN_ADD_TEST(${CMAKE_BINARY_DIR}/lib/${_test})
endforeach()

#set_property(TARGET *binary* PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
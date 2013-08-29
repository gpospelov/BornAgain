############################################################################
# CMakeLists.txt file for building TestFit functional tests
############################################################################

set(CMAKE_CXX_FLAGS "-DSTANDALONE")

set(list_of_tests
    "TestFit01"
    "TestFit02"
)

include_directories(${Boost_INCLUDE_DIRS})
#include_directories(${BornAgainCore_INCLUDE_DIRS})
foreach(_test ${list_of_tests})
    BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainFit_LIBRARY} ${BornAgainCore_LIBRARY})
    BORNAGAIN_ADD_TEST(${_test})
endforeach()

#set_property(TARGET *binary* PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
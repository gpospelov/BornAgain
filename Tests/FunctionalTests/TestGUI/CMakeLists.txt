# CMakeLists.txt file for building and running TestGUI functional tests

find_package(Qt5Widgets REQUIRED)


set(list_of_tests
    "TestGUI01"
    "TestGUI02"
    "TestGUI03"
    "TestGUI04"
    "TestGUI05"
)

# for some reason these flags doesn't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainGUI_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
)

foreach(_test ${list_of_tests})
   BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY} ${BornAgainGUI_LIBRARY})
   qt5_use_modules(${_test} Widgets Core Gui Script Designer PrintSupport)

   BORNAGAIN_ADD_TEST(${_test} INPUT_DIR ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/)
endforeach()



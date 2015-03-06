# CMakeLists.txt file for building and running TestGUI functional tests
if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()


find_package(Qt5Widgets REQUIRED)

set(list_of_tests
    "TestGUI01"
    "TestGUI02"
    "TestGUI03"
    "TestGUI04"
    "TestGUI05"
    "TestGUI06"
    "TestGUI07"
    "TestGUIBeamDivergence"
    "TestGUIDetectorResolution"
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
   #BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY} ${BornAgainGUI_LIBRARY})
   
   file(GLOB source_files "${_test}/*.cpp")
   file(GLOB include_files "${_test}/*.h")
   add_executable( ${_test} ${source_files} ${include_files})      
   target_link_libraries(${_test} ${BornAgainCore_LIBRARY} ${BornAgainGUI_LIBRARY}) 

   qt5_use_modules(${_test} Widgets Core Gui Script Designer PrintSupport)

   BORNAGAIN_ADD_TEST(${_test} INPUT_DIR ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/)
endforeach()



# CMakeLists.txt file for building and running TestGUI functional tests
if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

find_package(Qt5Widgets REQUIRED)

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

set(list_of_tests
    "TestGUI05"
#    "TestGUI06"
#    "TestGUI07"
#    "TestGUI08"
#    "TestGUIBeamDivergence"
#    "TestGUIDetectorResolution"
#    "TestGUIParticleDistribution"
#    "TestGUIParticleComposition"
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

# ------------------------------------------------------------------------
#
# New machinery
#
# ------------------------------------------------------------------------

set(list_of_tests
    "GUITestSuite/FormFactors"
    "GUITestSuite/CylindersAndPrisms"
    "GUITestSuite/RadialParaCrystal"
    "GUITestSuite/TwoDimParaCrystal"
    "GUITestSuite/CoreShellParticle"
)

# ------------------------------------------------------------------------
# Adding executables.
# The list of unique executable names is extracted from the list of tests
# ------------------------------------------------------------------------
foreach(_test ${list_of_tests})
    string(REPLACE "/" ";"  test_info ${_test})
    list(GET test_info 0 test_exe_name)
    list(APPEND list_of_executables ${test_exe_name})
endforeach()
list(REMOVE_DUPLICATES list_of_executables)
message(INFO "${list_of_executables}")

foreach(test_exe_name ${list_of_executables})
#   BORNAGAIN_EXECUTABLE(${test_exe_name} LOCATIONS ${test_exe_name} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY})

   file(GLOB source_files "${test_exe_name}/*.cpp")
   file(GLOB include_files "${test_exe_name}/*.h")
   add_executable( ${test_exe_name} ${source_files} ${include_files})
   target_link_libraries(${test_exe_name} ${BornAgainCore_LIBRARY} ${BornAgainGUI_LIBRARY})

   qt5_use_modules(${test_exe_name} Widgets Core Gui Script Designer PrintSupport)


endforeach()

# ------------------------------------------------------------------------
# Adding tests
# ------------------------------------------------------------------------
foreach(_test ${list_of_tests})
    string(REPLACE "/" ";"  test_info ${_test})
    list(LENGTH test_info len)
    list(GET test_info 0 test_exe_name)
    if(len EQUAL 2)
        list(GET test_info 1 test_argument)
    endif()

    message(INFO " _test ${_test} test_exe_name ${test_exe_name} test_argument ${test_argument}")
    set(test_input_args "${test_argument}")
    #set(test_input_args "${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/")

    BORNAGAIN_ADD_TEST2(${_test} ${test_exe_name} TEST_ARGUMENTS ${test_argument})
endforeach()


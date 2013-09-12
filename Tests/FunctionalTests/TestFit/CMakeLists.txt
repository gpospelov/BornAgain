############################################################################
# CMakeLists.txt file for building TestFit functional tests
############################################################################

set(CMAKE_CXX_FLAGS "-DSTANDALONE")

set(list_of_tests
    "TestFit01"
    "TestFit02"
)

# for some reason these flags doesn't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${BornAgainCore_INCLUDE_DIRS})
include_directories(${BornAgainFit_INCLUDE_DIRS})

foreach(_test ${list_of_tests})
    BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainFit_LIBRARY} ${BornAgainCore_LIBRARY})
    BORNAGAIN_ADD_TEST(${_test})
endforeach()

#foreach(_test ${list_of_tests})
#    file(GLOB source_files ${_test}/*.cpp)
#    add_executable(${_test} ${source_files})
#    target_link_libraries(${_test} ${BornAgainFit_LIBRARY} ${BornAgainCore_LIBRARY}) 
#    install (TARGETS ${_test} DESTINATION bin COMPONENT Applications)
#endforeach()



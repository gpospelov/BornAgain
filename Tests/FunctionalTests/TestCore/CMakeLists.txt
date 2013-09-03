############################################################################
# CMakeLists.txt file for building TestCore functional tests
############################################################################

set(CMAKE_CXX_FLAGS "-DSTANDALONE")

set(list_of_tests
    "IsGISAXS01"
#    "IsGISAXS02"
#    "IsGISAXS03"
#    "IsGISAXS04"
#    "IsGISAXS06"
#    "IsGISAXS07"
#    "IsGISAXS08"
#    "IsGISAXS09"
#    "IsGISAXS10"
#    "IsGISAXS11"
#    "IsGISAXS15"
#    "MesoCrystal1"
)


include_directories(${Boost_INCLUDE_DIRS})
foreach(_test ${list_of_tests})
#     file(GLOB source_files ${_test}/*.cpp)
#     add_executable(${_test} EXCLUDE_FROM_ALL ${source_files})
#     include_directories(${BornAgainCore_INCLUDE_DIRS})
#     include_directories(${Boost_INCLUDE_DIRS})
#     target_link_libraries(${_test} ${BornAgainCore_LIBRARY}) 
#     add_test( ${_test} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${_test} "${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/") # TestName ExeName Arguments
#     add_dependencies(check ${_test})
   BORNAGAIN_EXECUTABLE(${_test} LOCATIONS ${_test} EXCLUDE_FROM_ALL LIBRARIES ${BornAgainCore_LIBRARY})
   BORNAGAIN_ADD_TEST(${_test} INPUT_DIR ${CMAKE_BINARY_DIR}/Tests/ReferenceData/BornAgain/)
endforeach()


#set_property(TARGET ${_test} PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


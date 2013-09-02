############################################################################
# CMakeLists.txt file for building gtest library
############################################################################


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_VARIADIC_MAX=10")
endif()

add_subdirectory(gtest-1.6.0)
set_Target_properties(${gtest} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(gtest_LIBRARY_TYPE SHARED)






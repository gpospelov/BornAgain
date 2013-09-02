############################################################################
# CMakeLists.txt file for building gtest library
############################################################################


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_VARIADIC_MAX=10")
endif()

#set(BUILD_SHARED_LIBS ON)
add_subdirectory(gtest-1.6.0)
set_Target_properties(${gtest} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(gtest_LIBRARY_TYPE SHARED)

# ---

#include_directories(
#    ${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.6.0
#    ${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.6.0/include
#)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.6.0/src)

#add_library(
#    gtest
#    SHARED
#    gtest-1.6.0/src/gtest-all.cc
#)
#set_Target_properties(gtest PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
#set(gtest_LIBRARY_TYPE SHARED)





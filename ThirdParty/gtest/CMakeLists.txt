############################################################################
# CMakeLists.txt file for building gtest library
############################################################################


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_VARIADIC_MAX=10")
endif()

set(BUILD_SHARED_LIBS ON)
add_subdirectory(gtest-1.7.0)






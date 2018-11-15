############################################################################
# CMakeLists.txt file for building gtest library
############################################################################
if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()

# instructs CMake to consider libgtest.so as our project library (inspite of the fact, that
# it is not installed) and to provide @rpath instead of hardcoded links.
if(APPLE)
   set(CMAKE_MACOSX_RPATH 1)
endif()

option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." ON)
add_subdirectory(gtest-1.8.0)

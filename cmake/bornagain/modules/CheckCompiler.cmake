#---------------------------------------------------------------------------------------------------
#  CheckCompiler.cmake
#---------------------------------------------------------------------------------------------------

#----Test if clang setup works----------------------------------------------------------------------
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    execute_process(COMMAND ${CMAKE_C_COMPILER} -v
        OUTPUT_VARIABLE _clang_version_info
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REGEX REPLACE "^.*[ ]([0-9]+)\\.[0-9].*$" "\\1" CLANG_MAJOR "${_clang_version_info}")
    string(REGEX REPLACE "^.*[ ][0-9]+\\.([0-9]).*$" "\\1" CLANG_MINOR "${_clang_version_info}")
else()
    set(CLANG_MAJOR 0)
    set(CLANG_MINOR 0)
endif()

#---Obtain the major and minor version of the GNU compiler------------------------------------------
if (CMAKE_COMPILER_IS_GNUCXX)
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
        OUTPUT_VARIABLE _gcc_version_info
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REGEX REPLACE "^([0-9]+).*$"                   "\\1" GCC_MAJOR ${_gcc_version_info})
    string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*$"          "\\1" GCC_MINOR ${_gcc_version_info})
    string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*$" "\\1" GCC_PATCH ${_gcc_version_info})

    if(GCC_PATCH MATCHES "\\.+")
        set(GCC_PATCH "")
    endif()
    if(GCC_MINOR MATCHES "\\.+")
        set(GCC_MINOR "")
    endif()
    if(GCC_MAJOR MATCHES "\\.+")
        set(GCC_MAJOR "")
    endif()
    message(STATUS "Found GCC. Major version ${GCC_MAJOR}, minor version ${GCC_MINOR}")
    set(COMPILER_VERSION gcc${GCC_MAJOR}${GCC_MINOR}${GCC_PATCH})
else()
    set(GCC_MAJOR 0)
    set(GCC_MINOR 0)
endif()

#---Set a default build type for single-configuration CMake generators if no build type is set------
if(NOT CMAKE_BUILD_TYPE)
    #  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

#---Need to locate thead libraries and options to set properly some compilation flags---------------
find_package(Threads)

#---Setup details depending on the major platform type----------------------------------------------
if(CMAKE_SYSTEM_NAME MATCHES Linux)
    include(SetUpLinux)
elseif(APPLE)
    include(SetUpMacOS)
elseif(WIN32)
    include(SetUpWindows)
endif()

#---Setup details depending on the compiler type----------------------------------------------------
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_STANDARD 14)
else()
    message(FATAL_ERROR "No known c++ compiler found")
endif()

#---Print the final compiler flags------------------------------------------------------------------
message(STATUS "BornAgain Platform: ${BORNAGAIN_PLATFORM}")
message(STATUS "BornAgain Architecture: ${BORNAGAIN_ARCHITECTURE}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

set(all_cxx_flags ${CMAKE_CXX_FLAGS})
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(all_cxx_flags "${all_cxx_flags} ${CMAKE_CXX_FLAGS_RELEASE}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(all_cxx_flags "${all_cxx_flags} ${CMAKE_CXX_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(all_cxx_flags "${all_cxx_flags} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
endif()

message(STATUS "Compiler Flags: ${all_cxx_flags}")
message(STATUS "Shared linker Flags: ${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "Exe linker Flags: ${CMAKE_EXE_LINKER_FLAGS}")


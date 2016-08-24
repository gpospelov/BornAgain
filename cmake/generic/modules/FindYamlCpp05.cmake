# Find libyaml-cpp with API version 0.5
#
# Usage:
#   find_package(YamlCpp05 [REQUIRED] [QUIET])
#
# Sets the following variables:
#   - YAMLCPP_FOUND          .. true if library is found
#   - YAMLCPP_LIBRARIES      .. full path to library
#   - YAMLCPP_INCLUDE_DIR    .. full path to include directory
#
# Honors the following optional variables:
#   - YAMLCPP_INCLUDE_LOC    .. include directory path, to be searched before defaults
#   - YAMLCPP_LIBRARY_LOC    .. the library's directory path, to be searched before defaults
#   - YAMLCPP_STATIC_LIBRARY .. if true, find the static library version
#
# Copyright 2015 Joachim Wuttke, Forschungszentrum Jülich.
# Redistribution permitted.

include(CheckIncludeFileCXX)
include(CheckCXXSourceRuns)

# find the yaml-cpp include directory
if(WIN32)
    find_path(YAMLCPP_INCLUDE_DIR yaml.h PATHS ${CMAKE_INCLUDE_PATH}/yaml-cpp NO_SYSTEM_ENVIRONMENT_PATH)
else()
    find_path(YAMLCPP_INCLUDE_DIR yaml-cpp/yaml.h
        PATH_SUFFIXES include yaml-cpp/include yaml-cpp
        PATHS
        ${YAMLCPP_INCLUDE_LOC}
        ~/Library/Frameworks/
        /Library/Frameworks/
        /usr/local/
        /usr/
        /sw/ # Fink
        /opt/local/ # DarwinPorts
        /opt/csw/ # Blastwave
        /opt/
        )
endif()

set(CMAKE_REQUIRED_INCLUDES ${YAMLCPP_INCLUDE_DIR})
set(CMAKE_REQUIRED_QUIET True)

# first look for outdated yaml-cpp0.3 include files
unset(YAMLCPP_FOUND_03 CACHE)
CHECK_INCLUDE_FILE_CXX("yaml-cpp/aliasmanager.h" YAMLCPP_FOUND_03)
if(${YAMLCPP_FOUND_03})
    message(WARNING "Found include file for libyaml-cpp0.3. Most probably this precludes libyaml-cpp0.5 from being properly installed")
endif()

# now look for needed yaml-cpp0.5 include files
unset(YAMLCPP_FOUND_05 CACHE)
CHECK_INCLUDE_FILE_CXX("yaml-cpp/node/detail/iterator_fwd.h" YAMLCPP_FOUND_05)
if(${YAMLCPP_FOUND_05})
else()
    message(FATAL_ERROR "Include file for libyaml-cpp0.5 not found")
endif()

# attempt to find static library first if this is set
if(YAMLCPP_STATIC_LIBRARY)
    set(YAMLCPP_STATIC libyaml-cpp.a)
endif()

# find the yaml-cpp library
if(WIN32)
    find_library(YAMLCPP_LIBRARY NAMES yaml-cpp)
else()
    find_library(YAMLCPP_LIBRARY
        NAMES ${YAMLCPP_STATIC} yaml-cpp
        PATH_SUFFIXES lib64 lib
        PATHS
        ${YAMLCPP_LIBRARY_LOC}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt
        )
endif()

# try to compile, link, and run a test program
unset(YAMLCPP_RUNS CACHE)
set(CMAKE_REQUIRED_LIBRARIES ${YAMLCPP_LIBRARY}) 
check_cxx_source_runs("#include \"yaml-cpp/yaml.h\"\n#include <assert.h>\nint main() {\n    YAML::Node node = YAML::Load(\"[1, 2, 3]\");\n    assert(node.IsSequence());\n}" YAMLCPP_RUNS)
if(${YAMLCPP_RUNS})
else()
    message(FATAL_ERROR "Test of libyaml-cpp0.5 failed")
endif()

message(STATUS "Found FindYamlCpp05: ${YAMLCPP_LIBRARY}")
mark_as_advanced(YAMLCPP_INCLUDE_DIR YAMLCPP_LIBRARY)

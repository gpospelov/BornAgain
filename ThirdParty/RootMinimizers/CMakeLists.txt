############################################################################
# CMakeLists.txt file for building ROOT math/minuit2 package
############################################################################

set(library_name RootMinimizers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMATH_NO_PLUGIN_MANAGER -DHAS_MINUIT2 -DR__HAS_MATHMORE")

# directories to include
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
include_directories(${include_dirs})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../RootMathMore/inc)

# files to have in library
file(GLOB source_files
    "src/Minuit2/*.cxx"
    "src/Math/*.cxx"
    "src/Fit/*.cxx"
)

include_directories(${RootMathMore_INCLUDE_DIRS})

# making library
add_library(
    ${library_name}
    SHARED
    ${source_files}
)
set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)

# copying library into lib directory for functional tests
ADD_CUSTOM_COMMAND(
    TARGET ${library_name}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${libprefix}${library_name}${libsuffix}
    ${CMAKE_BINARY_DIR}/lib
)

# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

# dependencies
target_link_libraries(${library_name} ${GSL_LIBRARIES}) 

# -----------------------------------------------
# installation
# -----------------------------------------------
install (TARGETS ${library_name} DESTINATION lib)

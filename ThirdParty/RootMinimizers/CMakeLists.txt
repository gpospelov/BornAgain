############################################################################
# CMakeLists.txt file for building libRootMinimizers package
############################################################################

set(library_name RootMinimizers)

# source and include files
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
include_directories(${include_dirs})

file(GLOB source_files
    "src/Minuit2/*.cxx"
    "src/Math/*.cxx"
    "src/Fit/*.cxx"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMATH_NO_PLUGIN_MANAGER -DHAS_MINUIT2 -DR__HAS_MATHMORE")

# making library
add_library(
    ${library_name}
    SHARED
    ${source_files}
)
set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)

# external dependencies
include_directories(${GSL_INCLUDE_DIRS})
target_link_libraries(${library_name} ${GSL_LIBRARIES}) 

# copying library into lib directory for functional tests
#ADD_CUSTOM_COMMAND(
#    TARGET ${library_name}
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#    ${libprefix}${library_name}${libsuffix}
#    ${CMAKE_BINARY_DIR}/lib
#)

# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

# -----------------------------------------------
# installation
# -----------------------------------------------
install (TARGETS ${library_name} DESTINATION lib)

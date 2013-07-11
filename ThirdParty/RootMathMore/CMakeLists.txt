############################################################################
# CMakeLists.txt file for building libRootMathMore library
############################################################################
set(library_name RootMathMore)

# directories to include
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
include_directories(${include_dirs})

# files to have in library
file(GLOB source_files
    "src/*.cxx"
)

# making library
add_library(
    ${library_name}
    SHARED
    ${source_files}
)
set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)

# dependencies
target_link_libraries(${library_name} ${GSL_LIBRARIES}) 
target_link_libraries(${library_name} ${ROOT_LIBRARIES}) 

# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)


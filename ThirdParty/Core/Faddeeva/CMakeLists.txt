############################################################################
# CMakeLists.txt file for building libFaddeeva package
############################################################################
set(library_name Faddeeva)

# --- source and include files ---------
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
)
include_directories(${include_dirs})

file(GLOB source_files "*.cc")

file(GLOB include_files "*.hh")

# --- making library ------------
add_library(
    ${library_name}
    STATIC
    ${source_files} ${include_files}
)
set(${library_name}_INCLUDE_DIR ${include_dirs} CACHE INTERNAL "")
set(${library_name}_LIBRARY ${library_name} CACHE INTERNAL "")

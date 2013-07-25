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

if(ROOT_FOUND)
    target_link_libraries(${library_name} ${ROOT_LIBRARIES}) 
else()
    target_link_libraries(${library_name} ${RootMinimizers_LIBRARY}) 
    include_directories(${RootMinimizers_INCLUDE_DIRS})
endif()


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

#message("XXX ${CMAKE_MODULE_LINKER_FLAGS}")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-undefined")

# installation
install (TARGETS ${library_name} DESTINATION lib)

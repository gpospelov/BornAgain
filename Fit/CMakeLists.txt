############################################################################
# CMakeLists.txt file for building libBornAgainFit library
############################################################################
set(library_name BornAgainFit)

# directories to include
set(include_dirs 
    ${CMAKE_CURRENT_SOURCE_DIR}/Factory/inc
)
include_directories(${include_dirs})

# files to have in library
file(GLOB source_files
    "Factory/src/*.cpp"
    "Factory/src/*.cxx"
)

if(BORNAGAIN_PYTHON)
    file(GLOB pythonapi "PythonAPI/src/*.cpp")
    list(APPEND source_files ${pythonapi})
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/inc
    )
endif()


# making library
add_library(
    ${library_name}
    SHARED
    ${source_files}
)
set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)



# copying library into lib directory for functional tests
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/lib)
ADD_CUSTOM_COMMAND(
    TARGET ${library_name}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${libprefix}${library_name}${libsuffix}
    ${CMAKE_BINARY_DIR}/lib/
)

# dependencies
include_directories(${BornAgainCore_INCLUDE_DIRS})
target_link_libraries(${library_name} ${BornAgainCore_LIBRARY}) 
target_link_libraries(${library_name} ${ROOT_LIBRARIES}) 
target_link_libraries(${library_name} ${RootMathMore_LIBRARY}) 

# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

# -----------------------------------------------
# installation
# -----------------------------------------------
install (TARGETS ${library_name} DESTINATION lib)

# list of headers to install
file(GLOB include_files
    "Factory/inc/*.h"
)
install (FILES ${include_files} DESTINATION include)


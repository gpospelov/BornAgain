############################################################################
# CMakeLists.txt file for building libBornAgainCore library
############################################################################
set(library_name BornAgainCore)

# directories to include
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/Algorithms/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Fitting/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/FormFactors/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Samples/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/StandardSamples
    ${CMAKE_CURRENT_SOURCE_DIR}/Tools/inc
)
include_directories(${include_dirs})

# files to have in library
file(GLOB source_files
    "Algorithms/src/*.cpp"
    "Fitting/src/*.cpp"
    "FormFactors/src/*.cpp"
    "Geometry/src/*.cpp"
    "Samples/src/*.cpp"
    "StandardSamples/*.cpp"
    "Tools/src/*.cpp"
)

if(BORNAGAIN_PYTHON)
    file(GLOB pythonapi "PythonAPI/src/*.cpp" "PythonAPI/inc/__call_policies.pypp.hpp")
    list(APPEND ${source_files} ${pythonapi})
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

# dependencies
target_link_libraries(${library_name} ${FFTW_LIBRARY}) 
target_link_libraries(${library_name} ${Boost_LIBRARIES}) 
target_link_libraries(${library_name} ${GSL_LIBRARIES}) 
target_link_libraries(${library_name} ${PYTHON_LIBRARIES}) 

# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)


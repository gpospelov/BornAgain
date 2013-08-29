############################################################################
# CMakeLists.txt file for building libBornAgainCore library
############################################################################
set(library_name BornAgainCore)

# source and include files
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/Algorithms/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/FormFactors/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Samples/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/StandardSamples
    ${CMAKE_CURRENT_SOURCE_DIR}/Tools/inc
)
include_directories(${include_dirs})

file(GLOB source_files
    "Algorithms/src/*.cpp"
    "FormFactors/src/*.cpp"
    "Geometry/src/*.cpp"
    "Samples/src/*.cpp"
    "StandardSamples/*.cpp" 
    "Tools/src/*.cpp"
)

if(BORNAGAIN_PYTHON)
    file(GLOB pythonapi "PythonAPI/src/*.cpp" "PythonAPI/inc/__call_policies.pypp.hpp")
    list(APPEND source_files ${pythonapi})
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/inc
    )
endif()

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()

# making library
add_library(
    ${library_name}
    SHARED
    ${source_files}
)
set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)

# external dependencies
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${library_name} ${Boost_LIBRARIES}) 
target_link_libraries(${library_name} ${FFTW_LIBRARY}) 
target_link_libraries(${library_name} ${GSL_LIBRARIES}) 
target_link_libraries(${library_name} ${PYTHON_LIBRARIES}) 

# copying library into lib directory for functional tests
#execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/lib)
#ADD_CUSTOM_COMMAND(
#    TARGET ${library_name}
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#    ${libprefix}${library_name}${libsuffix}
#    ${CMAKE_BINARY_DIR}/lib/
#)

# python in windows required .yd extention for the library name
if(WIN32 AND BORNAGAIN_PYTHON)
    ADD_CUSTOM_COMMAND(
        TARGET ${library_name}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}${libsuffix}
        ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}".pyd"
    )
endif()

# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

# -----------------------------------------------
# installation
# -----------------------------------------------
install (TARGETS ${library_name} DESTINATION lib)
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION Examples FILES_MATCHING PATTERN "*.py")
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION Examples FILES_MATCHING PATTERN "README")
install (DIRECTORY ${CMAKE_SOURCE_DIR}/bin/ DESTINATION bin)

# list of headers to install
file(GLOB include_files
    "Algorithms/inc/*.h"
    "FormFactors/inc/*.h"
    "Geometry/inc/*.h"
    "Samples/inc/*.h"
    "Tools/inc/*.h"
)
install (FILES ${include_files} DESTINATION include)



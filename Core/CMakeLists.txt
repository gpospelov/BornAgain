############################################################################
# CMakeLists.txt file for building libBornAgainCore library
############################################################################
set(library_name BornAgainCore)

# --- source and include files ---
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

file(GLOB include_files 
    "Algorithms/inc/*.h"
    "FormFactors/inc/*.h"
    "Geometry/inc/*.h"
    "Samples/inc/*.h"
    "StandardSamples/*.h" 
    "Tools/inc/*.h"
)

if(BORNAGAIN_PYTHON)
    file(GLOB pythonapi_source "PythonAPI/src/*.cpp" "PythonAPI/inc/__call_policies.pypp.hpp")
    list(APPEND source_files ${pythonapi_source})
    file(GLOB pythonapi_include "PythonAPI/inc/*.h" "PythonAPI/inc/*.hpp")
    list(APPEND include_files ${pythonapi_include})
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/inc
    )
endif()

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()

# --- making library ---
add_library(
    ${library_name}
    SHARED
    ${source_files} ${include_files}
)
set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)
# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

# --- external dependencies ---
include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${FFTW_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
)
target_link_libraries(
    ${library_name}
    ${Boost_LIBRARIES}
    ${FFTW_LIBRARY}
    ${GSL_LIBRARIES}
)
if(BORNAGAIN_PYTHON)
    include_directories(${PYTHON_INCLUDE_DIRS} ${NUMPY_INCLUDE_DIR})
    target_link_libraries(${library_name} ${PYTHON_LIBRARIES})
endif()

# --- custom actions ---
# python in windows required .pyd extention for the library name
if(WIN32 AND BORNAGAIN_PYTHON)
    ADD_CUSTOM_COMMAND(
        TARGET ${library_name}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/bin/${libprefix}${library_name}${libsuffix}
        ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}".pyd"
    )
endif()

# -----------------------------------------------
# installation
# -----------------------------------------------
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION Examples COMPONENT Examples FILES_MATCHING PATTERN "*.py" )
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION Examples COMPONENT Examples FILES_MATCHING PATTERN "README")
install (DIRECTORY ${CMAKE_SOURCE_DIR}/bin DESTINATION . COMPONENT Libraries)

if(WIN32)
    set(libdir "bin")
else()
    set(libdir "lib")
endif()
install (TARGETS ${library_name} DESTINATION ${libdir} COMPONENT Libraries)

if(WIN32 AND BORNAGAIN_PYTHON)
    install(FILES 
    ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}.pyd
    DESTINATION lib COMPONENT Libraries)

    install(FILES 
    ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}.pyd
    DESTINATION bin COMPONENT Libraries)
endif()

# list of headers to install
file(GLOB include_files
    "Algorithms/inc/*.h"
    "FormFactors/inc/*.h"
    "Geometry/inc/*.h"
    "Samples/inc/*.h"
    "Tools/inc/*.h"
)
install (FILES ${include_files} DESTINATION include COMPONENT Headers)

# system libraries
if(WIN32)
    if(MSVC)
        set(boost_suffix "-vc110-mt-1_54.dll")
        install(FILES 
        ${CMAKE_LIBRARY_PATH}/boost_date_time${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_chrono${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_program_options${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_zlib${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_bzip2${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_iostreams${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_system${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_filesystem${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_python${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_regex${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/boost_thread${boost_suffix}
        ${CMAKE_LIBRARY_PATH}/libfftw3-3.dll
        DESTINATION bin COMPONENT Libraries)
    else()
        install (FILES ${Boost_LIBRARIES} DESTINATION bin COMPONENT Libraries)
        install (FILES ${FFTW_LIBRARY} DESTINATION bin COMPONENT Libraries)
        install (FILES ${GSL_LIBRARIES} DESTINATION bin COMPONENT Libraries)    
    endif()
endif()

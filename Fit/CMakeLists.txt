############################################################################
# CMakeLists.txt file for building libBornAgainFit library
############################################################################
set(library_name BornAgainFit)

# source and include files
set(include_dirs 
    ${CMAKE_CURRENT_SOURCE_DIR}/Factory/inc
)
include_directories(${include_dirs})

file(GLOB source_files
    "Factory/src/*.cpp"
    "Factory/src/*.cxx"
)

file(GLOB include_files
    "Factory/inc/*.h"
)

if(BORNAGAIN_PYTHON)
    file(GLOB pythonapi "PythonAPI/src/*.cpp")
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
    ${source_files} ${include_files}
)
set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)
# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

# --- dependencies ---
include_directories(
    ${BornAgainCore_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${RootMinimizers_INCLUDE_DIRS}
)
target_link_libraries(
    ${library_name}
    ${BornAgainCore_LIBRARY}
    ${Boost_LIBRARIES}
    ${RootMinimizers_LIBRARY}
)
if(BORNAGAIN_PYTHON)
    include_directories(${PYTHON_INCLUDE_DIRS})
    target_link_libraries(${library_name} ${PYTHON_LIBRARIES})
endif()

# --- custom actions
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
if(WIN32)
    set(libdir "bin")
else()
    set(libdir "lib")
endif()
install (TARGETS ${library_name} DESTINATION ${libdir} COMPONENT Libraries)

if(WIN32 AND BORNAGAIN_PYTHON)
    install(FILES ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}.pyd DESTINATION lib COMPONENT Libraries)
    install(FILES ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}.pyd DESTINATION bin COMPONENT Libraries)
endif()

# list of headers to install
file(GLOB include_files
    "Factory/inc/*.h"
)
install (FILES ${include_files} DESTINATION include  COMPONENT Headers)


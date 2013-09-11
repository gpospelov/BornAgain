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

# dependencies
include_directories(${BornAgainCore_INCLUDE_DIRS})
target_link_libraries(${library_name} ${BornAgainCore_LIBRARY}) 
target_link_libraries(${library_name} ${GSL_LIBRARIES}) 
message("XXX ${GSL_LIBRARIES}")
include_directories(${RootMinimizers_INCLUDE_DIRS})
target_link_libraries(${library_name} ${RootMinimizers_LIBRARY}) 
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${library_name} ${Boost_LIBRARIES}) 


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
install (TARGETS ${library_name} DESTINATION lib COMPONENT Libraries)
install (TARGETS ${library_name} DESTINATION bin COMPONENT Libraries)

if(WIN32 AND BORNAGAIN_PYTHON)
    install(FILES ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}.pyd DESTINATION lib COMPONENT Libraries)
    install(FILES ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}.pyd DESTINATION bin COMPONENT Libraries)
endif()

# list of headers to install
file(GLOB include_files
    "Factory/inc/*.h"
)
install (FILES ${include_files} DESTINATION include  COMPONENT Headers)


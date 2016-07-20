############################################################################
# CMakeLists.txt file for building libBornAgainFit library
############################################################################

set(library_name BornAgainFit)

if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()

# --- source and include files ------
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/FitKernel
    ${CMAKE_CURRENT_SOURCE_DIR}/StandardFits
    )
include_directories(${include_dirs})

file(GLOB fitkernel_source_files
    "FitKernel/*.cpp"
    "StandardFits/*.cpp"
    )

file(GLOB fitkernel_include_files
    "FitKernel/*.h"
    "StandardFits/*.h"
    )

set(source_files ${fitkernel_source_files})
set(include_files ${fitkernel_include_files})

if(BORNAGAIN_PYTHON)

    set(AUTO_DIR ${CMAKE_SOURCE_DIR}/auto/Wrap)
    file(MAKE_DIRECTORY ${AUTO_DIR})
    include_directories(${AUTO_DIR})

    set(include_dirs
        ${CMAKE_CURRENT_SOURCE_DIR}/FitKernel
        ${CMAKE_CURRENT_SOURCE_DIR}/StandardFits
        ${CMAKE_SOURCE_DIR}/Core/Basics
        ${CMAKE_SOURCE_DIR}/Core/Instrument
        ${CMAKE_SOURCE_DIR}/Core/Parametrization
        ${CMAKE_SOURCE_DIR}/Core/Simulation
        ${CMAKE_SOURCE_DIR}/Core/StandardSamples
        ${CMAKE_SOURCE_DIR}/Core/Tools
        ${CMAKE_SOURCE_DIR}/Core/InputOutput
        )
    include_directories(${include_dirs})

    if(BORNAGAIN_GENERATE_BINDINGS)

        set(WRAP_DIR ${CMAKE_SOURCE_DIR}/Wrap)
        set(TMP_DIR ${CMAKE_CURRENT_BINARY_DIR}/Wrap)
        file(MAKE_DIRECTORY ${TMP_DIR})

        GeneratePythonDocs(${AUTO_DIR}/doxygen_fit.i ${WRAP_DIR}/swig)

        set(swig_dependencies
            ${WRAP_DIR}/swig/libBornAgainFit.i
            ${WRAP_DIR}/swig/directors.i
            ${WRAP_DIR}/swig/extendFit.i
            ${WRAP_DIR}/swig/ignores.i
            ${WRAP_DIR}/swig/shared_pointers.i
            ${WRAP_DIR}/swig/warnings.i
            )
        foreach(FNAM ${swig_dependencies})
            if(NOT EXISTS ${FNAM})
                message(FATAL_ERROR "Could NOT find SWIG input ${FNAM}")
            endif()
        endforeach()
        set(swig_dependencies ${swig_dependencies} ${AUTO_DIR}/doxygen_fit.i)

        set(SWIG_FLAGS "-c++;-python;-o;${AUTO_DIR}/libBornAgainFit_wrap.cpp;-outdir;${TMP_DIR}")
        foreach(dir ${include_dirs})
            list(APPEND SWIG_FLAGS "-I${dir}")
        endforeach(dir)


        add_custom_command (
            OUTPUT ${AUTO_DIR}/libBornAgainFit.py
            COMMAND ${PYTHON_EXECUTABLE} ${WRAP_DIR}/swig/tweaks.py
                   ${TMP_DIR}/libBornAgainFit.py
                   ${AUTO_DIR}/libBornAgainFit.py
            DEPENDS ${TMP_DIR}/libBornAgainFit.py
            )
        add_custom_command (
            OUTPUT ${TMP_DIR}/libBornAgainFit.py
                   ${AUTO_DIR}/libBornAgainFit_wrap.h
                   ${AUTO_DIR}/libBornAgainFit_wrap.cpp
            COMMAND ${SWIG_EXECUTABLE} ${SWIG_FLAGS} ${WRAP_DIR}/swig/libBornAgainFit.i
            DEPENDS ${swig_dependencies} ${include_files}
            )

    endif(BORNAGAIN_GENERATE_BINDINGS)

    add_custom_target (
        ${library_name}_python
        COMMAND ${CMAKE_COMMAND} -E copy ${AUTO_DIR}/libBornAgainFit.py
             ${CMAKE_BINARY_DIR}/lib/libBornAgainFit.py
        DEPENDS ${AUTO_DIR}/libBornAgainFit.py
        )

    list(APPEND source_files "${AUTO_DIR}/libBornAgainFit_wrap.cpp")
    #list(APPEND include_files "${AUTO_DIR}/libBornAgainFit_wrap.h")

endif()

# --- definitions ---------
if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CORE_BUILD_DLL")
endif()

# --- making library ---------
add_library(
    ${library_name}
    SHARED
    ${source_files} ${include_files}
    )
set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)

if(BORNAGAIN_PYTHON)
    add_dependencies(${library_name} ${library_name}_python)
endif()

# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

# --- dependencies ---------
include_directories(
    ${BornAgainCore_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${RootMinimizers_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
    )

target_link_libraries(
    ${library_name}
    ${BornAgainCore_LIBRARY}
    ${Boost_LIBRARIES}
    ${RootMinimizers_LIBRARY}
    ${GSL_LIBRARIES}
    )

if(BORNAGAIN_PYTHON)
    include_directories(${PYTHON_INCLUDE_DIRS} ${NUMPY_INCLUDE_DIR})
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
    # for functional tests
    ADD_CUSTOM_COMMAND(
        TARGET ${library_name}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/bin/${libprefix}${library_name}${libsuffix}
        ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}${libsuffix}
        )

endif()

if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    #    set(link_flags "-Wl,-rpath,@loader_path/../..")
    set(link_flags "-Wl,-rpath,@loader_path/../../Frameworks")
    set_target_properties(${library_name}
        PROPERTIES
        LINK_FLAGS ${link_flags}
        )
endif()

# -----------------------------------------------
# installation
# -----------------------------------------------
install (TARGETS ${library_name} DESTINATION ${destination_lib} COMPONENT Libraries)
install (FILES ${fitkernel_include_files} DESTINATION ${destination_include}  COMPONENT Headers)
install (FILES ${CMAKE_BINARY_DIR}/lib/lib${library_name}.py DESTINATION ${destination_lib} COMPONENT Libraries) # required by SWIG

if(WIN32)
    if(BORNAGAIN_PYTHON)
        ADD_CUSTOM_COMMAND(
            TARGET ${library_name}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/bin/${libprefix}${library_name}${libsuffix}
            ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}".pyd"
            )

        install(FILES ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}.pyd DESTINATION ${destination_lib} COMPONENT Libraries)
        install(FILES ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}.pyd DESTINATION ${destination_bin} COMPONENT Libraries)
    endif()
endif()

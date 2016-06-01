############################################################################
# CMakeLists.txt file for building libBornAgainCore library
############################################################################
set(library_name BornAgainCore)
if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()


# --- source and include files ---------
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/Algorithms/
    ${CMAKE_CURRENT_SOURCE_DIR}/FormFactors/
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/
    ${CMAKE_CURRENT_SOURCE_DIR}/Samples/
    ${CMAKE_CURRENT_SOURCE_DIR}/StandardSamples
    ${CMAKE_CURRENT_SOURCE_DIR}/Tools/
    ${CMAKE_CURRENT_SOURCE_DIR}/InputOutput
    )

set(bornagain_swig_dir ${CMAKE_CURRENT_SOURCE_DIR}/../dev-tools/swig)


include_directories(${include_dirs})

file(GLOB core_source_files
    "Algorithms/*.cpp"
    "FormFactors/*.cpp"
    "Geometry/*.cpp"
    "Samples/*.cpp"
    "StandardSamples/*.cpp"
    "Tools/*.cpp"
    "InputOutput/*.cpp"
    )

file(GLOB core_include_files
    "Algorithms/*.h"
    "FormFactors/*.h"
    "Geometry/*.h"
    "Samples/*.h"
    "StandardSamples/*.h"
    "Tools/*.h"
    "InputOutput/*.h"
    )

set(source_files ${core_source_files})
set(include_files ${core_include_files})

if(BORNAGAIN_PYTHON)

    file(GLOB pythonapi_source "PythonAPI/*.cpp")
    list(APPEND source_files ${pythonapi_source})
    file(GLOB pythonapi_include "PythonAPI/*.hpp")
    list(APPEND include_files ${pythonapi_include})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/)


    if(BORNAGAIN_GENERATE_BINDINGS)

        set(SWIG_FLAGS "")
        list(APPEND SWIG_FLAGS "-c++")
        list(APPEND SWIG_FLAGS "-python")

        foreach(dir ${include_dirs})
            list(APPEND SWIG_FLAGS "-I${dir}")
        endforeach(dir)

        set(swig_dependencies
            ${bornagain_swig_dir}/libBornAgainCore.i
            ${bornagain_swig_dir}/directors.i
            ${bornagain_swig_dir}/doxygen_core.i
            ${bornagain_swig_dir}/extends.i
            ${bornagain_swig_dir}/ignores.i
            ${bornagain_swig_dir}/shared_pointers.i
            ${bornagain_swig_dir}/warnings.i
            )

        add_custom_command (
            OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainCore.py ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainCore_wrap.h ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainCore_wrap.cxx
            COMMAND ${SWIG_EXECUTABLE} ${SWIG_FLAGS} ${bornagain_swig_dir}/libBornAgainCore.i
            COMMAND ${PYTHON_EXECUTABLE} ${bornagain_swig_dir}/tweaks.py ${bornagain_swig_dir}/libBornAgainCore.py ${bornagain_swig_dir}/libBornAgainCore.py
            COMMAND ${CMAKE_COMMAND} -E copy ${bornagain_swig_dir}/libBornAgainCore.py ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainCore.py
            COMMAND ${CMAKE_COMMAND} -E copy ${bornagain_swig_dir}/libBornAgainCore_wrap.cxx ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainCore_wrap.cxx
            COMMAND ${CMAKE_COMMAND} -E copy ${bornagain_swig_dir}/libBornAgainCore_wrap.h ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainCore_wrap.h
            COMMAND ${CMAKE_COMMAND} -E remove ${bornagain_swig_dir}/libBornAgainCore.py
            COMMAND ${CMAKE_COMMAND} -E remove ${bornagain_swig_dir}/libBornAgainCore_wrap.cxx
            COMMAND ${CMAKE_COMMAND} -E remove ${bornagain_swig_dir}/libBornAgainCore_wrap.h
            DEPENDS ${swig_dependencies}
            )

        # autogenerate doxygen.i from doxygen comments
        if(BORNAGAIN_GENERATE_PYTHON_DOCS)
            configure_file(${CMAKE_SOURCE_DIR}/Doc/Doxygen/DoxyfileSwig.in ${CMAKE_CURRENT_BINARY_DIR}/PythonAPI/Doxyfile @ONLY)

            add_custom_command(
                OUTPUT ${bornagain_swig_dir}/doxygen_core.i
                COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/PythonAPI/Doxyfile
                COMMAND ${PYTHON_EXECUTABLE} ${bornagain_swig_dir}/doxy2swig.py ${CMAKE_CURRENT_BINARY_DIR}/Doc/xml/index.xml ${bornagain_swig_dir}/doxygen_core.i
                DEPENDS ${include_files}
                )

        endif(BORNAGAIN_GENERATE_PYTHON_DOCS)

    endif(BORNAGAIN_GENERATE_BINDINGS)

    add_custom_target (
        ${library_name}_python
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainCore.py ${CMAKE_BINARY_DIR}/lib/libBornAgainCore.py
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainCore.py
        )

    # manually add: if does not exist, will be created by swig
    list(APPEND source_files "PythonAPI/libBornAgainCore_wrap.cxx")
    #list(APPEND include_files "PythonAPI/libBornAgainCore_wrap.h")


    # add_custom_target(
    #   ${library_name}_python
    #   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainCore.py ${CMAKE_BINARY_DIR}/lib/libBornAgainCore.py
    #   )
    configure_file(../dev-tools/python-setup/bornagain/plot_utils.py ${CMAKE_BINARY_DIR}/lib/plot_utils/__init__.py COPYONLY)

endif()


#--- definitions ---------
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


# --- external dependencies ---------

target_link_libraries(${library_name} ${CMAKE_THREAD_LIBS_INIT})

if(BORNAGAIN_TIFF_SUPPORT)
    add_definitions(-DBORNAGAIN_TIFF_SUPPORT)
    include_directories(${TIFF_INCLUDE_DIR})
    target_link_libraries(${library_name} ${TIFF_LIBRARIES})
endif()

include_directories(${EIGEN3_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${FFTW_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR} ${Faddeeva_INCLUDE_DIR})
target_link_libraries(${library_name} ${Boost_LIBRARIES} ${FFTW_LIBRARY} ${GSL_LIBRARIES}
    ${Faddeeva_LIBRARY})

if(BORNAGAIN_OPENMPI)
    add_definitions(-DBORNAGAIN_OPENMPI)
    include_directories(${MPI_INCLUDE_PATH})
    target_link_libraries(${library_name} ${MPI_LIBRARIES})
endif()

if(BORNAGAIN_PYTHON)
    add_definitions(-DBORNAGAIN_PYTHON)
    include_directories(${PYTHON_INCLUDE_DIRS} ${NUMPY_INCLUDE_DIR})
    target_link_libraries(${library_name} ${PYTHON_LIBRARIES})
endif()

if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    set(link_flags "-Wl,-rpath,@loader_path/../../Frameworks")
    set_target_properties(${library_name}
        PROPERTIES
        LINK_FLAGS ${link_flags}
        )
endif()


# --- installation ---------
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "*.py" )
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "README")
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "*.gz")
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/ DESTINATION ${destination_examples} COMPONENT Examples FILES_MATCHING PATTERN "*.png")
install (DIRECTORY ${CMAKE_SOURCE_DIR}/Examples/cpp DESTINATION ${destination_examples} COMPONENT Examples)
install (TARGETS ${library_name} DESTINATION ${destination_lib} COMPONENT Libraries)
install (FILES ${CMAKE_BINARY_DIR}/lib/lib${library_name}.py DESTINATION ${destination_lib} COMPONENT Libraries) # required by swig
install (FILES ${core_include_files} DESTINATION ${destination_include} COMPONENT Headers)

if(WIN32)
    # python in windows required .pyd extention for the library name
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
        # for functional tests
        # install(FILES ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}.dll DESTINATION ${destination_lib} COMPONENT Libraries)
        ADD_CUSTOM_COMMAND(
            TARGET ${library_name}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/bin/${libprefix}${library_name}${libsuffix}
            ${CMAKE_BINARY_DIR}/lib/${libprefix}${library_name}${libsuffix}
            )

    endif()

    # system libraries
    FOREACH(Boost_lib ${Boost_LIBRARIES})
        get_filename_component(UTF_BASE_NAME ${Boost_lib} NAME_WE)
        get_filename_component(UTF_PATH ${Boost_lib} PATH)
        message(STATUS "Boost dll: ${UTF_PATH}/${UTF_BASE_NAME}.dll")
        install(FILES ${UTF_PATH}/${UTF_BASE_NAME}.dll
            DESTINATION ${destination_lib} COMPONENT Libraries)
    ENDFOREACH()

    get_filename_component(UTF_BASE_NAME ${PYTHON_LIBRARIES} NAME_WE)
    get_filename_component(UTF_PATH ${PYTHON_EXECUTABLE} PATH)
    message(STATUS "Python dll: ${UTF_PATH}/${UTF_BASE_NAME}.dll")
    install(FILES ${UTF_PATH}/${UTF_BASE_NAME}.dll
        DESTINATION ${destination_lib} COMPONENT Libraries)

    install(FILES
        ${CMAKE_LIBRARY_PATH}/libfftw3-3.dll
        ${CMAKE_LIBRARY_PATH}/libtiff.dll
        DESTINATION ${destination_lib} COMPONENT Libraries)

else()
    # installing thisbornagain.sh
    install(FILES ${destination_runtime_configs}/frombin_setup_paths.sh
        ${destination_runtime_configs}/frombin_setup_paths.csh
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
        DESTINATION ${destination_libexec})

    # creating bin directory for links
    if(NOT BORNAGAIN_APPLE_BUNDLE AND NOT BUILD_DEBIAN)
        install(CODE "
            FILE(MAKE_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/${destination_bin}\")
        " COMPONENT Runtime)

        # making links
        install(CODE "
        execute_process(COMMAND \${CMAKE_COMMAND} -E create_symlink
        \"../libexec/${destination_suffix}/frombin_setup_paths.sh\" \"thisbornagain.sh\"
        WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/${destination_bin}\")
        " COMPONENT Runtime)

        install(CODE "
        execute_process(COMMAND \${CMAKE_COMMAND} -E create_symlink
        \"../libexec/${destination_suffix}/frombin_setup_paths.csh\" \"thisbornagain.csh\"
        WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/${destination_bin}\")
        " COMPONENT Runtime)
    else()

        install(FILES ${CMAKE_SOURCE_DIR}/dev-tools/python-setup/bornagain_python_install.py
            DESTINATION ${destination_libexec})

    endif()


endif()

if(NOT BORNAGAIN_APPLE_BUNDLE)
    # installing bornagain/__init__.py and utilites
    install (DIRECTORY ${CMAKE_SOURCE_DIR}/dev-tools/python-setup/bornagain DESTINATION ${destination_lib} COMPONENT Libraries)
    install (FILES "${destination_runtime_configs}/__init__.py" DESTINATION ${destination_lib}/bornagain COMPONENT Libraries)
else()
    install (DIRECTORY ${CMAKE_SOURCE_DIR}/dev-tools/python-setup/bornagain DESTINATION ${destination_libexec} COMPONENT Libraries)
    install (FILES "${destination_runtime_configs}/__init__.py" DESTINATION ${destination_libexec}/bornagain COMPONENT Libraries)
endif()

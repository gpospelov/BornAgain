############################################################################
# CMakeLists.txt file for building libBornAgainCore library
############################################################################
set(library_name BornAgainCore)
if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()


# --- source and include files ---------
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/Algorithms/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/FormFactors/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Samples/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/StandardSamples
    ${CMAKE_CURRENT_SOURCE_DIR}/Tools/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/InputOutput
)
include_directories(${include_dirs})

file(GLOB core_source_files
    "Algorithms/src/*.cpp"
    "FormFactors/src/*.cpp"
    "Geometry/src/*.cpp"
    "Samples/src/*.cpp"
    "StandardSamples/*.cpp"
    "Tools/src/*.cpp"
    "InputOutput/*.cpp"
)

file(GLOB core_include_files
    "Algorithms/inc/*.h"
    "FormFactors/inc/*.h"
    "Geometry/inc/*.h"
    "Samples/inc/*.h"
    "StandardSamples/*.h"
    "Tools/inc/*.h"
    "InputOutput/*.h"
)

set(source_files ${core_source_files})
set(include_files ${core_include_files})

if(BORNAGAIN_PYTHON)
    file(GLOB pythonapi_source "PythonAPI/src/*.cpp" "PythonAPI/inc/__call_policies.pypp.hpp")
    list(APPEND source_files ${pythonapi_source})
    file(GLOB pythonapi_include "PythonAPI/inc/*.h" "PythonAPI/inc/*.hpp")
    list(APPEND include_files ${pythonapi_include})
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/inc
	)

      # JMF: this should be done more carefully in the future
      configure_file(../dev-tools/python-bindings/swig/libBornAgainCore.py ../lib/libBornAgainCore.py COPYONLY)
      configure_file(../dev-tools/python-setup/bornagain/plot_utils.py ../lib/plot_utils/__init__.py COPYONLY)

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
# exposing library name and list of include directories outside
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)


# --- external dependencies ---------
if(BORNAGAIN_TIFF_SUPPORT)
    add_definitions(-DBORNAGAIN_TIFF_SUPPORT)
    include_directories(${TIFF_INCLUDE_DIR})
    target_link_libraries(${library_name} ${TIFF_LIBRARIES})
endif()

include_directories(${EIGEN3_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${FFTW_INCLUDE_DIR} ${GSL_INCLUDE_DIR})
target_link_libraries(${library_name} ${Boost_LIBRARIES} ${FFTW_LIBRARY} ${GSL_LIBRARIES})

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
    set(boost_suffix "-vc120-mt-1_59.dll")
    
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
    ${CMAKE_LIBRARY_PATH}/libtiff.dll
    "C:/Anaconda/Python27.dll"
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


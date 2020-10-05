############################################################################
# CMakeLists.txt file for building libBornAgainCore
############################################################################

set(name Core)
set(lib BornAgain${name})

# --- source and include files ---

file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

if((NOT Cerf_IS_CPP) AND (NOT WIN32)) # TEMPORARY
    list(APPEND source_files ${CMAKE_SOURCE_DIR}/ThirdParty/Core/cerf_wrapper/cerf_ptr.c)
endif()
if(${Cerf_IS_CPP})
    string(APPEND CMAKE_CXX_FLAGS " -DCERF_AS_CPP=ON")
endif()

if(BORNAGAIN_PYTHON)
    list(APPEND source_files "${AUTO_DIR}/lib${lib}_wrap.cpp")
endif()

# --- making library ---

add_library(${lib} SHARED ${source_files})
set_target_properties(${lib} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${lib}_LIBRARY_TYPE SHARED)

if(BORNAGAIN_PYTHON)
    SwigLib(${name} ${lib} ${CMAKE_CURRENT_BINARY_DIR}/Wrap)

    add_custom_target(
        ${lib}_python
        COMMAND ${CMAKE_COMMAND}
            -E copy ${AUTO_DIR}/lib${lib}.py ${CMAKE_BINARY_DIR}/lib/lib${lib}.py
        COMMAND ${CMAKE_COMMAND}
            -E copy ${AUTO_DIR}/lib${lib}.py ${CMAKE_BINARY_DIR}/lib/bornagain/lib${lib}.py
        DEPENDS ${AUTO_DIR}/lib${lib}.py
        )

    if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
        # suppress warnings from auto-generated code (last updated for Swig 4.0.1)
        set_source_files_properties(${AUTO_DIR}/lib${lib}_wrap.cpp
            PROPERTIES COMPILE_OPTIONS
            "-Wno-unused-parameter;-Wno-missing-field-initializers;-Wno-sometimes-uninitialized;\
-Wno-deprecated-declarations")
    endif()

    add_dependencies(${lib} ${lib}_python)

    target_compile_definitions(${lib} PUBLIC -DBORNAGAIN_PYTHON)
    target_include_directories(${lib} PUBLIC ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
    target_link_libraries(${lib} ${Python3_LIBRARIES})

endif(BORNAGAIN_PYTHON)

# exposing library name and list of include directories outside
set(${lib}_LIBRARY ${lib} PARENT_SCOPE)

if(BORNAGAIN_PYTHON)
    add_dependencies(${lib} swig_runtime)
endif()

# --- external dependencies ---

target_link_libraries(${lib} ${BornAgainFit_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

if(BORNAGAIN_TIFF_SUPPORT)
    target_compile_definitions(${lib} PUBLIC -DBORNAGAIN_TIFF_SUPPORT)
    target_include_directories(${lib} PUBLIC ${TIFF_INCLUDE_DIR})
    target_link_libraries(${lib} ${TIFF_LIBRARIES})
endif()

target_include_directories(${lib}
    PUBLIC ${CMAKE_SOURCE_DIR} ${Boost_INCLUDE_DIRS} ${FFTW3_INCLUDE_DIR} ${GSL_INCLUDE_DIR}
    ${tspectrum_INCLUDE_DIR}
    ${Cerf_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/ThirdParty/Core/cerf_wrapper # TEMPORARY
    SYSTEM PUBLIC ${EIGEN3_INCLUDE_DIRS}
    )
if(BORNAGAIN_GUI)
    target_include_directories(${lib} PUBLIC ${Qt5Core_INCLUDE_DIRS})
    target_link_libraries(${lib} ${Qt5Core_LIBRARIES})
endif()

target_link_libraries(${lib} ${Boost_LIBRARIES} ${FFTW3_LIBRARIES} ${GSL_LIBRARIES}
    ${tspectrum_LIBRARY} ${Cerf_LIBRARIES})

if(BORNAGAIN_MPI)
    add_definitions(-DBORNAGAIN_MPI)
    include_directories(${MPI_INCLUDE_PATH})
    target_link_libraries(${lib} ${MPI_LIBRARIES})
endif()

if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    set(link_flags "-Wl,-rpath,@loader_path/../../Frameworks")
    set_target_properties(${lib} PROPERTIES LINK_FLAGS ${link_flags})
endif()

# --- installation ---

install(TARGETS ${lib} DESTINATION ${destination_lib} COMPONENT Libraries)
install(FILES ${CMAKE_BINARY_DIR}/lib/lib${lib}.py
    DESTINATION ${destination_lib} COMPONENT Libraries) # required by swig

foreach(file ${include_files})
    get_filename_component(dir ${file} DIRECTORY)
    install(FILES ${file} DESTINATION ${destination_include}/${name}/${dir})
endforeach()

if(WIN32)
    # python in windows required .pyd extension for the library name
    if(BORNAGAIN_PYTHON)
        add_custom_command(
            TARGET ${lib}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/bin/${libprefix}${lib}${libsuffix}
            ${CMAKE_BINARY_DIR}/lib/${libprefix}${lib}".pyd"
            )
        install(FILES ${CMAKE_BINARY_DIR}/lib/${libprefix}${lib}.pyd
            DESTINATION ${destination_lib} COMPONENT Libraries)
        add_custom_command(
            TARGET ${lib}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/bin/${libprefix}${lib}${libsuffix}
            ${CMAKE_BINARY_DIR}/lib/${libprefix}${lib}${libsuffix}
            )
    endif()
endif()

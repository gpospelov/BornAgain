############################################################################
# CMakeLists.txt file for building libBornAgainFit
############################################################################

set(name Fit)
set(lib BornAgain${name})

# --- source and include files ---

file(GLOB source_files */*.cpp)
file(GLOB include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */*.h)

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

# --- external dependencies ---

target_include_directories(${lib}
    PUBLIC ${RootMinimizers_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(${lib} ${RootMinimizers_LIBRARY} ${Boost_LIBRARIES})


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

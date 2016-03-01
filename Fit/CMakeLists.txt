############################################################################
# CMakeLists.txt file for building libBornAgainFit library
############################################################################
set(library_name BornAgainFit)
if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()


# --- source and include files ------
set(include_dirs 
    ${CMAKE_CURRENT_SOURCE_DIR}/FitKernel/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/StandardFits
)
include_directories(${include_dirs})

file(GLOB fitkernel_source_files
    "FitKernel/src/*.cpp"
    "FitKernel/src/*.cxx"
    "StandardFits/*.cpp"
)

file(GLOB fitkernel_include_files
    "FitKernel/inc/*.h"
    "StandardFits/*.h"
)

set(source_files ${fitkernel_source_files})
set(include_files ${fitkernel_include_files})

if(BORNAGAIN_PYTHON)
    file(GLOB source_pythonapi "PythonAPI/*.cpp")
    list(APPEND source_files ${source_pythonapi})
    file(GLOB include_pythonapi "PythonAPI/*.h")
    list(APPEND include_files ${include_pythonapi})

    set(include_dirs
      ${CMAKE_CURRENT_SOURCE_DIR}/FitKernel/inc
      ${CMAKE_CURRENT_SOURCE_DIR}/StandardFits
      ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/
      ${CMAKE_SOURCE_DIR}/Core/PythonAPI/
      ${CMAKE_SOURCE_DIR}/Core/Algorithms/inc
      ${CMAKE_SOURCE_DIR}/Core/FormFactors/inc
      ${CMAKE_SOURCE_DIR}/Core/Geometry/inc
      ${CMAKE_SOURCE_DIR}/Core/Samples/inc
      ${CMAKE_SOURCE_DIR}/Core/StandardSamples
      ${CMAKE_SOURCE_DIR}/Core/Tools/inc
      ${CMAKE_SOURCE_DIR}/Core/InputOutput
      )
    include_directories(${include_dirs})


    if(BORNAGAIN_GENERATE_BINDINGS)
      #set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainFit.i PROPERTIES CPLUSPLUS ON)
      #set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainFit.i PROPERTIES SWIG_FLAGS "-includeall")
      set(SWIG_FLAGS "")
      list(APPEND SWIG_FLAGS "-c++")
      list(APPEND SWIG_FLAGS "-python")

      foreach(dir ${include_dirs})
        list(APPEND SWIG_FLAGS "-I${dir}")
      endforeach(dir)

    
      add_custom_command (
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainFit_wrap.cxx ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainFit_wrap.h ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainFit.py
        COMMAND ${SWIG_EXECUTABLE} ${SWIG_FLAGS} ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainFit.i
        COMMAND sed -i "'s/_libBornAgainFit.ICloneable_transferToCPP(self)/self.__disown__()/g'" ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainFit.py
        DEPENDS PythonAPI/libBornAgainFit.i ${include_files}
        )
    

    endif()

  add_custom_target (
    ${library_name}_python
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainFit.py ${CMAKE_BINARY_DIR}/lib/libBornAgainFit.py
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/libBornAgainFit.py
    )
  
  list(APPEND source_files "PythonAPI/libBornAgainFit_wrap.cxx")
  list(APPEND include_files "PythonAPI/libBornAgainFit_wrap.h")
      
   # configure_file(../dev-tools/python-bindings/swig/libBornAgainFit.py ../lib/libBornAgainFit.py COPYONLY)
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



############################################################################
# Tests/Functional/PyCore/presistence/CMakeLists.txt
############################################################################

set(PYPERSIST_REF_DIR ${REFERENCE_DIR}/PyPersist)
set(PYPERSIST_OUT_DIR ${BUILD_REF_DIR}/PyPersist)
file(MAKE_DIRECTORY ${PYPERSIST_OUT_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPYPERSIST_OUT_DIR=\\\"${PYPERSIST_OUT_DIR}\\\"")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPYPERSIST_REF_DIR=\\\"${PYPERSIST_REF_DIR}\\\"")

file(GLOB PY_EXAMPLES
    "${PY_EXAMPLES_DIR}/simulation/ex*/*.py"
    "${PY_EXAMPLES_DIR}/fitting/ex01*/*.py"
    )

# for some reason these flags doesn't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

include_directories(
    ${BornAgainCore_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/Core/Simulation
    ${CMAKE_CURRENT_SOURCE_DIR}/../../TestMachinery
)

add_executable(PyPersistenceTest RunPyPersistenceTest.cpp PyPersistenceTest.h PyPersistenceTest.cpp)
target_link_libraries(PyPersistenceTest BornAgainCore BornAgainTestMachinery)
foreach(script ${PY_EXAMPLES})
    get_filename_component(script_dir  ${script} DIRECTORY)
    get_filename_component(script_name ${script} NAME_WE)
    get_filename_component(script_ext  ${script} EXT)
    if (NOT ${script_ext} STREQUAL ".py" )
        message(SEND_ERROR
            "Unexpected file name extension '${script_ext}' in Python script ${script}")
        continue()
    endif()
    add_test(PyPersistenceTest/${script_name}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PyPersistenceTest ${script_dir} ${script_name})
endforeach()

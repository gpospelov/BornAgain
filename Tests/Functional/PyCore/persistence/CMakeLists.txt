############################################################################
# Tests/Functional/PyCore/suite/CMakeLists.txt
############################################################################

set(test_cases
    ApproximationDA
    ApproximationLMA
    ToBeReplacedByGlob
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
foreach(test_case ${test_cases})
    add_test(PyPersistenceTest/${test_case}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PyPersistenceTest ${test_case})
endforeach()

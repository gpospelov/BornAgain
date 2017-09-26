set(test CoreSpecial)

set(test_cases
    BatchSimulation
    PolDWBAMagCylinders
#    CoreIO
)

# for some reason these flags doesn't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

include_directories(
    ${BornAgainCore_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS} ${NUMPY_INCLUDE_DIR}
    ${EIGEN3_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../TestMachinery
)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

add_executable(${test} ${include_files} ${source_files})
target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)

foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()

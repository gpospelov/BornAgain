set(test PyEmbedded)

set(test_cases
    SysPath
    ImportNumpy
    FunctionCall
    MethodCall
    CompiledFunction
    ObjectExtract
    ExportToPythonAndBack
    ModuleFunctionsList
)

include_as_system_directory("${EIGEN3_INCLUDE_DIR}")

include_directories(
    ${BornAgainCore_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS} 
    ${NUMPY_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../TestMachinery
    ${CMAKE_SOURCE_DIR}/auto/Wrap
)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

add_executable(${test} ${include_files} ${source_files})
target_link_libraries(${test} BornAgainCore BornAgainTestMachinery)

foreach(test_case ${test_cases})
    add_test(${test}/${test_case} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test} ${test_case})
endforeach()


############################################################################
# Core unit tests
############################################################################
set(test UnitTestNumeric)

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()

if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

file(GLOB source_files "*.cpp" "../utilities/TestAll.cpp")
file(GLOB include_files "*.h")

add_executable(${test} ${source_files} ${include_files})
target_link_libraries(${test} ${BornAgainCore_LIBRARY} gtest)

# Registering in ctest section
add_test(${test} ${test})
set_tests_properties(${test} PROPERTIES LABELS "Fullcheck")

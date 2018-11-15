############################################################################
# GUI unit tests
############################################################################

set(test UnitTestGUI)

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()

if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/Tests/UnitTests/utilities)

set(CMAKE_AUTOMOC ON)
add_executable(${test} ${source_files} ${include_files})
target_link_libraries(${test} ${BornAgainGUI_LIBRARY} gtest)
target_link_libraries(${test} Qt5::Core Qt5::Test)

# add execution of TestCore just after compilation
add_custom_target(${test}_run ALL DEPENDS ${test} COMMAND ${test})

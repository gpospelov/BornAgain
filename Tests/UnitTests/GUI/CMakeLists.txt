
set(TestName TestGUI)

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5Widgets REQUIRED)

include_as_system_directory("${EIGEN3_INCLUDE_DIR}")
include_directories(
    ../utilities
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
    ${BornAgainGUI_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${gtest_SOURCE_DIR}
    ${gtest_SOURCE_DIR}/include
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_LINKED_AS_SHARED_LIBRARY=1")

set(CMAKE_AUTOMOC ON)

add_executable(${TestName} ${source_files} ${include_files})

target_link_libraries(${TestName} ${BornAgainGUI_LIBRARY} gtest)

qt5_use_modules(${TestName} Widgets Core Gui Designer PrintSupport Network Test)

# add execution of TestCore just after compilation
add_custom_target(${TestName}Target ALL DEPENDS TestGUI COMMAND ${TestName})

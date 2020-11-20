#   ************************************************************************************************
#
#   BornAgain: simulate and fit scattering at grazing incidence
#
#!  @file      Tests/Functional/Core/Std/CMakeLists.txt
#!  @brief     Builds Core standard tests.
#
#!  @homepage  http://www.bornagainproject.org
#!  @license   GNU General Public License v3 or higher (see COPYING)
#!  @copyright Forschungszentrum Jülich GmbH 2018
#!  @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
#
#   ************************************************************************************************

include(GoogleTest) # provides gtest_discover_tests

set(test TestCoreStd)

file(GLOB source_files "*.cpp" "../../Std/Run.cpp")

add_executable(${test} ${source_files} ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)
target_include_directories(${test} PUBLIC
    ${BornAgainCore_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/ThirdParty/common/gtest/gtest-1.8.0/include)
target_link_libraries(${test} BornAgainCore gtest)

gtest_discover_tests(${test} DISCOVERY_TIMEOUT 300 TEST_PREFIX Core.)

#   ************************************************************************************************
#
#   BornAgain: simulate and fit scattering at grazing incidence
#
#!  @file      Tests/Functional/GUI/Std/CMakeLists.txt
#!  @brief     Builds GUI standard tests.
#
#              .../Std/TestAll.cpp provides main, which essentially runs RUN_ALL_TESTS().
#              RUN_ALL_TESTS is a gtest macro that runs tests defined by TEST_F macros.
#              .../Std/Run.cpp uses such TEST_F macros to define our standard test cases.
#              Check.cpp provides a callback function that executes one GUI tests:
#              Run a given simulation directly, and through GUI model, and compare results.
#
#!  @homepage  http://www.bornagainproject.org
#!  @license   GNU General Public License v3 or higher (see COPYING)
#!  @copyright Forschungszentrum Jülich GmbH 2018
#!  @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
#
#   ************************************************************************************************

include(GoogleTest) # provides gtest_discover_tests

set(test TestGuiStd)

set(source_files Check.cpp ../../Std/Run.cpp ${CMAKE_SOURCE_DIR}/Tests/GTestWrapper/TestAll.cpp)

add_executable(${test} ${source_files})
target_compile_options(${test} PUBLIC -DGUI_STD_TEST)

target_include_directories(${test} PUBLIC
    ${BornAgainGUI_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/ThirdParty/common/gtest/gtest-1.8.0/include)
target_link_libraries(${test} BornAgainGUI gtest)

gtest_discover_tests(${test} DISCOVERY_TIMEOUT 300 TEST_PREFIX Gui.)

#################################################################################
#
#  BornAgain: simulate and fit scattering at grazing incidence
#
#  @file      cmake/bornagain/modules/AddGTest.cmake
#  @brief     Implements macro ADD_GTEST(..)
#
#  @homepage  http://www.bornagainproject.org
#  @license   GNU General Public License v3 or higher (see COPYING)
#  @copyright Forschungszentrum Jülich GmbH 2016
#  @authors   Scientific Computing Group at MLZ Garching
#  @authors   J. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
#
##################################################################################

#  @brief Build test target from ${subdir}/main.cpp.

#  stage=0: test run at compile time
#  stage=1: test run upon "ctest"="make check"

MACRO(ADD_GTEST project subdir libs stage)
    set(TEST_NAME ${project}UnitTest${subdir})
    set(EXE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME})
    file(GLOB include_files ${subdir}/*.h)
    add_executable(${TEST_NAME} ${subdir}/main.cpp ${include_files})
    target_link_libraries(${TEST_NAME} gtest ${libs})
    if    (${stage} EQUAL 0)
        # Execute test just after compilation
        add_custom_command(TARGET ${TEST_NAME} POST_BUILD COMMAND ${EXE})
    elseif(${stage} EQUAL 1)
        # Put test under control of CTest
        add_test(${TEST_NAME} ${EXE})
    else()
        message(FATAL_ERROR "invalid parameter stage=${stage} in ADD_GTEST")
    endif()
ENDMACRO()

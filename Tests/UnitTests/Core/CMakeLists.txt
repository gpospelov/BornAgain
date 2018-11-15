############################################################################
# Core unit tests
############################################################################
set(test UnitTestCore)

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()

if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

#ADD_GTEST(${test} "Axes" ${libs} 0)
#ADD_GTEST(${test} "Sample" ${libs} 0)
#ADD_GTEST(${test} "Fresnel" ${libs} 0)
#ADD_GTEST(${test} "Detector" ${libs} 0)
#ADD_GTEST(${test} "ExportToPython" ${libs} 0)
#ADD_GTEST(${test} "Parameters" ${libs} 0)
#ADD_GTEST(${test} "DataStructure" ${libs} 0)
#ADD_GTEST(${test} "Other" ${libs} 0)
#ADD_GTEST(${test} "SimulationElement" ${libs} 0)
#ADD_GTEST(${test} "Fitting" ${libs} 0)
#ADD_GTEST(${test} "Numeric0" ${libs} 2)
#ADD_GTEST(${test} "Numeric1" ${libs} 2)


file(GLOB source_files "*/*.cpp")
file(GLOB include_files "*/*.h")
list(APPEND source_files "TestAll.cpp" "../utilities/FormFactorTest.cpp")

add_executable(${test} ${source_files} ${include_files})
target_link_libraries(${test} ${BornAgainCore_LIBRARY} gtest)

# add execution of TestCore just after compilation
add_custom_target(${test}_run ALL DEPENDS ${test} COMMAND ${test})

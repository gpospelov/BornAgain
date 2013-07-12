############################################################################
# CMakeLists.txt file for building gtest library
############################################################################


add_subdirectory(gtest-1.6.0)
set_Target_properties(${gtest} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(gtest_LIBRARY_TYPE SHARED)


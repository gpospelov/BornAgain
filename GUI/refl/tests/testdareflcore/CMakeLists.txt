set(executable_name testdareflcore)

include(GoogleTest)

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

if(WIN32)
    add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY)
endif()

# necessary for Qt creator and clang code model
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_AUTOMOC ON)
add_executable(${executable_name} ${source_files} ${include_files})
target_link_libraries(${executable_name} gtest gmock Qt5::Core Qt5::Test dareflcore darefltestmachinery)

# to make clang code model in Qt creator happy
target_compile_features(${executable_name} PUBLIC cxx_std_17)

gtest_discover_tests(${executable_name})

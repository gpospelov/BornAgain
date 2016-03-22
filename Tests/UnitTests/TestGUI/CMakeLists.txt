############################################################################
# CMakeLists.txt file for building and running unit tests
############################################################################
if(POLICY CMP0020)
cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
cmake_policy(SET CMP0043 NEW)
endif()

enable_testing()

file(GLOB source_files "*.cpp")
file(GLOB include_files "*.h")

find_package(Qt5Widgets REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
    ${BornAgainGUI_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
)


# to build executable right in lib directory to not to have problems with finding libBornAgainCore.dll under Windows
#set_property(TARGET TestGUI PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_AUTOMOC ON)

add_executable(TestGUI ${source_files} ${include_files})

target_link_libraries(TestGUI
    ${BornAgainCore_LIBRARY}
    ${BornAgainGUI_LIBRARY}
)

qt5_use_modules(TestGUI Widgets Core Gui Designer PrintSupport Network Test)

add_test( TestGUI TestGUI) # TestName ExeName

# add execution of TestCore just after compilation
add_custom_command(TARGET TestGUI POST_BUILD COMMAND TestGUI)


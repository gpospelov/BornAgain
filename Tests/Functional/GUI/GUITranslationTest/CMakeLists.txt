set(test_name GUITranslationTest)

if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

find_package(Qt5Widgets REQUIRED)

# for some reason these flags doesn't propagated here by SetUpWindows.cmake
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainGUI_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../TestMachinery
)

add_executable(${test_name} main.cpp GUITranslationTest.cpp GUITranslationTest.h)
target_link_libraries(${test_name} BornAgainCore BornAgainGUI BornAgainTestMachinery)
qt5_use_modules(${test_name} Widgets Core Gui Designer PrintSupport Network)

add_test(${test_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_name})


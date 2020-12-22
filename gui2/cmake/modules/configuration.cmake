# -----------------------------------------------------------------------------
# Modules
# -----------------------------------------------------------------------------

include(CTest)
include(CodeTools)
include(GenerateExportHeader)
include(GNUInstallDirs)

# -----------------------------------------------------------------------------
# Variables
# -----------------------------------------------------------------------------

get_filename_component(DAREFL_PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)

set(DAREFL_TESTOUTPUT_DIR ${CMAKE_BINARY_DIR}/test_output_darefl)

# -----------------------------------------------------------------------------
# Directories
# -----------------------------------------------------------------------------

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${DAREFL_TESTOUTPUT_DIR})

# directory for autogenerated configs
set(DAREFL_AUTOGEN_DIR ${CMAKE_BINARY_DIR}/autogen/darefl)
file(MAKE_DIRECTORY ${DAREFL_AUTOGEN_DIR})

# -----------------------------------------------------------------------------
# Dependencies
# -----------------------------------------------------------------------------

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 5.12 COMPONENTS Widgets Core Gui PrintSupport REQUIRED)
find_package(Threads)

get_target_property(Qt5Widgets_location Qt5::Widgets LOCATION_Release)
message(STATUS " Qt5 libraries : ${Qt5Widgets_LIBRARIES} ${Qt5Widgets_location}")
message(STATUS " Qt5 Includes  : ${Qt5Widgets_INCLUDE_DIRS}")

# -----------------------------------------------------------------------------
# Generating config files
# -----------------------------------------------------------------------------

configure_file(${DAREFL_PROJECT_DIR}/cmake/scripts/testconfig.h.in  ${DAREFL_AUTOGEN_DIR}/testconfig.h @ONLY)

# -----------------------------------------------------------------------------
# Compile options
# -----------------------------------------------------------------------------

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
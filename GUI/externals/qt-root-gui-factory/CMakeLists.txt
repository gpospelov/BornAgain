############################################################################
# CMakeLists.txt file for building libQtRoot
############################################################################

cmake_minimum_required(VERSION 2.8.9)
set(library_name QtRoot)

# source files
file(GLOB source_files "src/*.cxx")
file(GLOB include_files "inc/*.h")

set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${include_dirs})

ROOT_GENERATE_DICTIONARY(G__QtRoot ${include_files} LINKDEF LinkDef.h)

# --- making library ---
add_library(
    ${library_name}
    SHARED
    ${source_files} ${include_files} G__QtRoot.cxx
)
set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

# --- dependencies ---
include_directories(
    ${ROOT_INCLUDE_DIR}
    ${GQt_INCLUDE_DIRS}
)

target_link_libraries(${library_name} ${ROOT_LIBRARIES})

#find_package(Qt5Widgets REQUIRED)
qt5_use_modules(${library_name} Widgets)


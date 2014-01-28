############################################################################
# CMakeLists.txt file for building libQtRoot
############################################################################

cmake_minimum_required(VERSION 2.8.9)

if(POLICY CMP0020)
cmake_policy(SET CMP0020 NEW)
endif()

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
    STATIC
    ${source_files} ${include_files} G__QtRoot.cxx
)
#set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
#set(${library_name}_LIBRARY_TYPE SHARED)

set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)

# --- dependencies ---
message("XXX ${GQt_LIBRARY}")
message("XXX ${ROOT_LIBRARIES} ")
include_directories(
    ${GQt_INCLUDE_DIRS}
    ${ROOT_INCLUDE_DIR}
)

target_link_libraries(
    ${library_name} 
    ${GQt_LIBRARY}
    ${ROOT_LIBRARIES} 
)

#find_package(Qt5Widgets REQUIRED)
qt5_use_modules(${library_name} Widgets)

# --- installation ---
#install (TARGETS ${library_name} DESTINATION bin COMPONENT Libraries)

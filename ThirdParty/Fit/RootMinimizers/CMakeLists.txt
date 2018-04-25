############################################################################
# CMakeLists.txt file for building libRootMinimizers package
############################################################################
set(library_name RootMinimizers)

# --- source and include files ---------
set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${include_dirs})

file(GLOB source_files
    "Minuit2/*.cxx"
    "Math/*.cxx"
    "Fit/*.cxx"
    "TMVA/*.cxx"
)

file(GLOB include_files
    "Minuit2/*.h"
    "Math/*.h"
    "Fit/*.h"
    "TMVA/*.h"
)

# --- definitions ---------
add_definitions(-DWARNINGMSG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMATH_NO_PLUGIN_MANAGER -DHAS_MINUIT2 -DR__HAS_MATHMORE")
if(NOT WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
else()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244 /wd4267")
endif()

# --- making library ------------
add_library(${library_name} STATIC ${source_files} ${include_files})
set(${library_name}_INCLUDE_DIRS ${include_dirs} CACHE INTERNAL "")
set(${library_name}_LIBRARY ${library_name} CACHE INTERNAL "")

# --- external dependencies ---
include_directories(${GSL_INCLUDE_DIR})
target_link_libraries(${library_name} ${GSL_LIBRARIES})

include_directories(${Boost_INCLUDE_DIRS})

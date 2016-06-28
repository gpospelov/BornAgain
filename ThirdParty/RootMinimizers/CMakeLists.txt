############################################################################
# CMakeLists.txt file for building libRootMinimizers package
############################################################################
set(library_name RootMinimizers)

# --- source and include files ---------
set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${include_dirs})

file(GLOB source_files
    "src/Minuit2/*.cxx"
    "src/Math/*.cxx"
    "src/Fit/*.cxx"
    "src/TMVA/*.cxx"
)

file(GLOB include_files
    "inc/Fit/*.h"
    "inc/Math/*.h"
    "inc/Minuit2/*.h"
    "src/Math/*.h"
    "inc/TMVA/*.h"
)

# --- definitions ---------
add_definitions(-DWARNINGMSG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMATH_NO_PLUGIN_MANAGER -DHAS_MINUIT2 -DR__HAS_MATHMORE")
if(NOT WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
endif()

# --- making library ------------
add_library(${library_name} STATIC ${source_files} ${include_files})
set(${library_name}_INCLUDE_DIRS ${include_dirs} CACHE INTERNAL "")
set(${library_name}_LIBRARY ${library_name} CACHE INTERNAL "")

# --- external dependencies ---
include_directories(${GSL_INCLUDE_DIR})
target_link_libraries(${library_name} ${GSL_LIBRARIES})

include_directories(${Boost_INCLUDE_DIRS})

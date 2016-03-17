############################################################################
# CMakeLists.txt file for building BornAgain/App executable
############################################################################

set(executable_name App)

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
include_directories(${include_dirs})

# source files
file(GLOB source_files "*.cpp")

# include files
file(GLOB include_files "*.h")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc ")
endif()

# dictionaries
ROOT_GENERATE_DICTIONARY(AppDict DrawHelper.h TreeEventStructure.h  LINKDEF AppLinkDef.h)

# --- dependencies ---
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${ROOT_INCLUDE_DIR}
    ${RootMinimizers_INCLUDE_DIRS}
)

add_executable(${executable_name} ${source_files} AppDict.cxx ${include_files})

target_link_libraries(${executable_name}
    ${Boost_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
    ${ROOT_LIBRARIES}
)

# --- Installation ---
install (TARGETS ${executable_name} DESTINATION ${destination_bin} COMPONENT Applications)

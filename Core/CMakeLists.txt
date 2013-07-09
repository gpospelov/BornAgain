############################################################################
# CMakeLists.txt file for building BornAgain core package
############################################################################


set(LIBRARY_NAME BornAgainCore)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Algorithms/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Fitting/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/FormFactors/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Samples/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/StandardSamples/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Tools/inc
)

file(GLOB BornAgainCore_SRC
    "Algorithms/src/*.cpp"
    "Fitting/src/*.cpp"
    "FormFactors/src/*.cpp"
    "Geometry/src/*.cpp"
    "Samples/src/*.cpp"
    "StandardSamples/*.cpp"
    "Tools/src/*.cpp"
)

if(BORNAGAIN_PYTHON)
    file(GLOB BornAgainCore_PythonAPI "PythonAPI/src/*.cpp" "PythonAPI/inc/__call_policies.pypp.hpp")
    list(APPEND BornAgainCore_SRC ${BornAgainCore_PythonAPI})
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/inc
    )
endif()

add_library(
    ${LIBRARY_NAME}
    SHARED
    ${BornAgainCore_SRC}
)
set_Target_properties(${LIBRARY_NAME} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(BornAgainCore_LIBRARY_TYPE SHARED)


# --- Eigen3 ---
find_package(Eigen3)
include_directories(${EIGEN3_INCLUDE_DIR})

# --- FFTW3 ---
find_package(FFTW)
include_directories(${FFTW_INCLUDE_DIR})
target_link_libraries(${LIBRARY_NAME} ${FFTW_LIBRARY}) 

# --- Boost ---
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF)
set(boost_libraries_required program_options iostreams system filesystem regex thread)
if(BORNAGAIN_PYTHON)
    list(APPEND boost_libraries_required python)
endif()
find_package(Boost 1.46.0 COMPONENTS ${boost_libraries_required})
target_link_libraries(${LIBRARY_NAME} ${Boost_LIBRARIES}) 

# --- GSL ---
find_package(GSL)
include_directories(${GSL_INCLUDE_DIR})
target_link_libraries(${LIBRARY_NAME} ${GSL_LIBRARIES}) 

# --- Python ---
if(BORNAGAIN_PYTHON)

    find_package(PythonInterp)

    find_package(PythonLibs)
    include_directories(${PYTHON_INCLUDE_DIRS})
    target_link_libraries(${LIBRARY_NAME} ${PYTHON_LIBRARIES}) 

    find_package(Numpy)
    include_directories(${NUMPY_INCLUDE_DIR})
endif()




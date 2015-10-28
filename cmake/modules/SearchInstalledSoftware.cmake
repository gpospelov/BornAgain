# Search for installed software required by BornAgain

if(BORNAGAIN_OPENMPI)
    message(STATUS "Configuring with OpenMPI support")
    find_package(MPI REQUIRED)
endif()


# --- Eigen3 ---
set(EIGEN3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/eigen3)
message(STATUS "Build in version of Eigen3 will be used")

# --- FFTW3 ---
find_package(FFTW REQUIRED)

# --- BOOST ---
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions(-DBOOST_ALL_DYN_LINK) # line is needed for MSVC
#add_definitions(-DBOOST_LIB_DIAGNOSTIC) # shows during compilation auto-linked libraries
if(WIN32)
    set(boost_libraries_required date_time chrono program_options zlib bzip2 iostreams system filesystem regex thread)
else()
    set(boost_libraries_required date_time chrono program_options iostreams system filesystem regex thread)
endif()
if(BORNAGAIN_PYTHON OR BORNAGAIN_GUI)
    list(APPEND boost_libraries_required python)
endif()
find_package(Boost 1.48.0 COMPONENTS ${boost_libraries_required} REQUIRED)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")


# --- GSL ---
find_package(GSL REQUIRED)

# -----------------------------------------------------------------------------
# Tiff
# -----------------------------------------------------------------------------
if(BORNAGAIN_TIFF_SUPPORT)
    find_package(TIFF 4.0.2)
    if(NOT TIFF_FOUND)
        set(BORNAGAIN_TIFF_SUPPORT OFF)
        message(STATUS "--> LibTIFF was not found on the system , disabling tiff support.")
    endif()
endif()



# --- Python ---
if(BORNAGAIN_PYTHON OR BORNAGAIN_GUI)

    find_package(PythonInterp 2.7 REQUIRED)
    message(STATUS "--> PYTHON_VERSION_STRING: ${PYTHON_VERSION_STRING}, PYTHON_EXECUTABLE:${PYTHON_EXECUTABLE}")

    find_package(PythonLibs 2.7)
    message(STATUS "--> PYTHON_LIBRARIES: ${PYTHON_LIBRARIES}, PYTHON_INCLUDE_DIRS:${PYTHON_INCLUDE_DIRS} PYTHONLIBS_VERSION_STRING:${PYTHONLIBS_VERSION_STRING}")

    ValidatePythonIntstallation()

    message(STATUS "--> PYTHON_LIBRARIES: ${PYTHON_LIBRARIES}, PYTHON_INCLUDE_DIRS:${PYTHON_INCLUDE_DIRS} PYTHONLIBS_VERSION_STRING:${PYTHONLIBS_VERSION_STRING}")

    if(NOT PYTHONLIBS_FOUND)
        message(FATAL_ERROR "No Python library has been found")
    endif()

    find_package(Numpy REQUIRED)

endif()


# --- ROOT ---
if(BORNAGAIN_APP)
    find_package(ROOT)
endif()

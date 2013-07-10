
# --- Eigen3 ---
find_package(Eigen3)
include_directories(${EIGEN3_INCLUDE_DIR})

# --- FFTW3 ---
find_package(FFTW)
include_directories(${FFTW_INCLUDE_DIR})

# --- Boost ---
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF)
set(boost_libraries_required program_options iostreams system filesystem regex thread)
if(BORNAGAIN_PYTHON)
    list(APPEND boost_libraries_required python)
endif()
find_package(Boost 1.46.0 COMPONENTS ${boost_libraries_required})

# --- GSL ---
find_package(GSL)
include_directories(${GSL_INCLUDE_DIR})

# --- Python ---
if(BORNAGAIN_PYTHON)

    find_package(PythonInterp)

    find_package(PythonLibs)
    include_directories(${PYTHON_INCLUDE_DIRS})

    find_package(Numpy)
    include_directories(${NUMPY_INCLUDE_DIR})
endif()

# --- ROOT ---
find_package(ROOT)
if(ROOT_FOUND)
    include_directories(${ROOT_INCLUDE_DIR})
endif()

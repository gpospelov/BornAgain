# Search for installed software required by BornAgain

# --- Eigen3 ---
find_package(Eigen3 3.1.0)
if(NOT EIGEN3_FOUND) 
    set(EIGEN3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/eigen3)
    message(STATUS "--> Build in version of Eigen3 will be used")
endif()

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

#if(NOT BUILTIN_GSL)
#    find_package(GSL REQUIRED)
#    if(GSL_FOUND)
#        include_directories(${GSL_INCLUDE_DIR})
#    else()
#        message(STATUS "No GSL has been found. Install it, or run cmake -DBUILTIN_GSL=ON to use build in GSL installation.")
#    endif()
#endif()

#if(BUILTIN_GSL)
#    set(gsl_version 1.9)
#    include(ExternalProject)
#    message(STATUS "Downloading and building GSL version ${gsl_version}")
#    ExternalProject_Add(
#      GSL
#      URL http://mirror.switch.ch/ftp/mirror/gnu/gsl/gsl-${gsl_version}.tar.gz
#      INSTALL_DIR ${CMAKE_BINARY_DIR}
#      CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix <INSTALL_DIR> --disable-shared
#    )
#    set(GSL_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/include)
#    set(GSL_LIBRARIES -L${CMAKE_BINARY_DIR}/lib -lgsl -lgslcblas -lm)
#endif()


# --- Python ---
if(BORNAGAIN_PYTHON OR BORNAGAIN_GUI)
    find_package(PythonInterp)
    # important to find interpreter and libraries from same python version
    set(PythonLibs_FIND_VERSION ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR})
    find_package(PythonLibs REQUIRED)
    if(NOT PYTHONLIBS_FOUND)
        message(SEND_ERROR "No python libraries have been found")
    endif()
    find_package(Numpy REQUIRED)
endif()


# --- ROOT ---
find_package(ROOT)

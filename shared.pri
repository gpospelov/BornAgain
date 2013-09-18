# -----------------------------------------------------------------------------
# Common settings for all BornAgain compilations
# -----------------------------------------------------------------------------

CONFIG  += BORNAGAIN_PYTHON # provide python bindings compilation

win32 {
    MAKE_COMMAND = mingw32-make
    SONAME = dll
    DEFINES += _WIN32
}
macx|unix {
    MAKE_COMMAND = make
    SOPREFIX = lib
    SONAME = so
    QMAKE_EXTENSION_SHLIB = $$SONAME
}

# -----------------------------------------------------------------------------
# checking common prerequisites
# -----------------------------------------------------------------------------
lessThan(QT_VERSION, 4.5) {
    error("BornAgain requires Qt 4.5 or greater")
}

!macx:!unix:!win32 {
  error("Unknown operation system")
}

# -----------------------------------------------------------------------------
# for debug set environment variable 'export BORNAGAIN_DEBUG=yes'
# -----------------------------------------------------------------------------
env_debug_variable = $$(BORNAGAIN_DEBUG)
isEqual(env_debug_variable, "yes") {
  #message("Compiling with DEBUG option")
  CONFIG += debug
}


# -----------------------------------------------------------------------------
# Global variables
# -----------------------------------------------------------------------------
BornAgainCore_INCLUDE_DIR = $$PWD/Core/Algorithms/inc $$PWD/Core/FormFactors/inc $$PWD/Core/Geometry/inc $$PWD/Core/Samples/inc $$PWD/Core/Tools/inc $$PWD/Core/StandardSamples
BornAgainCore_LIBRARY = $$PWD/lib/$${SOPREFIX}BornAgainCore.$${SONAME}

BornAgainFit_INCLUDE_DIR = $$PWD/Fit/Factory/inc
BornAgainFit_LIBRARY = $$PWD/lib/$${SOPREFIX}BornAgainFit.$${SONAME}

RootMinimizers_INCLUDE_DIR = $${PWD}/ThirdParty/RootMinimizers/inc
RootMinimizers_LIBRARY = $$PWD/lib/$${SOPREFIX}RootMinimizers.$${SONAME}

gtest_INCLUDE_DIR= $${PWD}/ThirdParty/gtest/gtest-1.6.0/include
gtest_LIBRARY = $$PWD/lib/$${SOPREFIX}gtest.$${SONAME}

# -----------------------------------------------------------------------------
# general external libraries
# -----------------------------------------------------------------------------

# --- checking gsl header ---
GSL_HEADERFILE = gsl/gsl_sf_bessel.h
macx|unix {
  GSL_HEADER_LOCATIONS = /opt/local/include /usr/local/include /usr/include
}
win32 {
  GSL_HEADER_LOCATIONS = "C:/opt/local/include"
}
for(dir, GSL_HEADER_LOCATIONS): isEmpty(GSL_INCLUDE_DIR): exists($${dir}/$${GSL_HEADERFILE}): GSL_INCLUDE_DIR = $${dir}
isEmpty(GSL_INCLUDE_DIR): message("Can't find" $${GSL_HEADERFILE} "in" $${GSL_HEADER_LOCATIONS})
GSL_LIBRARY_DIR = $$replace(GSL_INCLUDE_DIR,"include","lib")
macx|unix {
    GSL_LIBRARY = -L$${GSL_LIBRARY_DIR} -lgsl -lgslcblas
}
win32 {
    GSL_LIBRARY = -L$${GSL_LIBRARY_DIR} -lgsl-0 -lgslcblas-0
}

# --- checking eigen headers ---
EIGEN_HEADERFILE = Eigen/Core
macx|unix {
  EIGEN_HEADER_LOCATIONS = /opt/local/include /opt/local/include/eigen3  /usr/local/include /usr/include
}
win32 {
  EIGEN_HEADER_LOCATIONS = "C:/opt/local/include"
}
for(dir, EIGEN_HEADER_LOCATIONS): isEmpty(EIGEN_INCLUDE_DIR): exists($${dir}/$${EIGEN_HEADERFILE}): EIGEN_INCLUDE_DIR = $${dir}
isEmpty(EIGEN_INCLUDE_DIR) {
    #message("Can't find" $${EIGEN_HEADERFILE} "in" $${EIGEN_HEADER_LOCATIONS} " Using build in eigen3")
    EIGEN_INCLUDE_DIR = $$PWD/ThirdParty/eigen3
}

# --- checking fftw3 ---
FFTW3_HEADERFILE = fftw3.h
macx|unix {
  FFTW3_HEADER_LOCATIONS = /opt/local/include /usr/local/include /usr/include
  FFTW3_LIBNAME = fftw3
}
win32 {
  FFTW3_HEADER_LOCATIONS = "C:/opt/local/include"
  FFTW3_LIBNAME = fftw3-3
}
for(dir, FFTW3_HEADER_LOCATIONS): isEmpty(FFTW3_INCLUDE_DIR): exists($${dir}/$${FFTW3_HEADERFILE}): FFTW3_INCLUDE_DIR = $${dir}
isEmpty(FFTW3_INCLUDE_DIR): message("Can't find" $${FFTW3_HEADERFILE} "in" $${FFTW3_HEADER_LOCATIONS})
FFTW3_LIBRARY_DIR = $$replace(FFTW3_INCLUDE_DIR,"include","lib")
FFTW3_LIBRARY = -L$${FFTW3_LIBRARY_DIR} -l$${FFTW3_LIBNAME}

# --- checking boost ---
BOOST_HEADERFILE = boost/version.hpp
macx|unix {
  BOOST_HEADER_LOCATIONS = /opt/local/include /usr/local/include /usr/include
}
win32 {
  BOOST_HEADER_LOCATIONS = "C:/opt/local/include"
  BOOST_LIB_SUFFIX = -mgw48-mt-1_54
}
for(dir, BOOST_HEADER_LOCATIONS): isEmpty(BOOST_INCLUDE_DIR): exists($${dir}/$${BOOST_HEADERFILE}): BOOST_INCLUDE_DIR = $${dir}
isEmpty(BOOST_INCLUDE_DIR): message("Can't find" $${BOOST_HEADERFILE} "in" $${BOOST_HEADER_LOCATIONS})
BOOST_LIBFILES = libboost*
# following check only works on *nix systems
macx|unix {
  BOOST_LIB_LOCATIONS = /opt/local/lib /usr/local/lib /usr/lib64 /usr/lib
  for(dir, BOOST_LIB_LOCATIONS): isEmpty(BOOST_LIBRARY_DIR) {
    NumberOfSuchFiles=$$system(ls $${dir}/$${BOOST_LIBFILES} 2> /dev/null | wc -l)
    !isEqual(NumberOfSuchFiles, 0): BOOST_LIBRARY_DIR = $${dir}
  }
}
win32 {
  BOOST_LIBRARY_DIR = "C:/Boost/lib"
}
isEmpty(BOOST_LIBRARY_DIR): message("Can't find" $${BOOST_LIBFILES} "in" $${BOOST_LIB_LOCATIONS})
BOOST_LIBRARY = -L$${BOOST_LIBRARY_DIR} -lboost_program_options$${BOOST_LIB_SUFFIX} -lboost_iostreams$${BOOST_LIB_SUFFIX} -lboost_system$${BOOST_LIB_SUFFIX} -lboost_filesystem$${BOOST_LIB_SUFFIX} -lboost_regex$${BOOST_LIB_SUFFIX} -lboost_thread$${BOOST_LIB_SUFFIX}
# checking special case when system doesn't have libboost_thread library but have libboost_thread-mt
!win32 {
  NumberOfSuchFiles=$$system(ls $${BOOST_LIBRARY_DIR}/libboost_thread-mt* 2> /dev/null | wc -l)
  !isEqual(NumberOfSuchFiles, 0) {
    # library libboost_thread-mt exists
    BOOST_LIBRARY = $$replace(BOOST_LIBRARY, "-lboost_thread", "-lboost_thread-mt")
  }
}

isEmpty(GSL_INCLUDE_DIR): error("missed dependency:" $${GSL_HEADERFILE})
isEmpty(FFTW3_INCLUDE_DIR): error("missed dependency:" $${FFTW3_HEADERFILE})
isEmpty(BOOST_INCLUDE_DIR): error("missed dependency:" $${BOOST_HEADERFILE})
isEmpty(BOOST_LIBRARY_DIR): error("missed dependency:" $${BOOST_LIBFILES})


# -----------------------------------------------------------------------------
# temporary workaround for compilation in JCNS
# -----------------------------------------------------------------------------
env_jcns_variable = $$(BORNAGAIN_JCNS)
isEqual(env_jcns_variable, "yes") {
  CONFIG += BORNAGAIN_JCNS
}

CONFIG(BORNAGAIN_JCNS) {
  message("Special config for JCNS")
  INCLUDEPATH += /usr/users/jcns/pospelov/software/include
  OLD_LIBS = $$LIBS
  LIBS = -L/usr/users/jcns/pospelov/software/lib -L/usr/local/lib -L/usr/lib64 \
         -lgsl -lgslcblas -lfftw3 -lboost_program_options -lboost_iostreams \
         -lboost_system -lboost_signals  -lboost_filesystem -lboost_regex \
         -lboost_thread $$OLD_LIBS
}

# -----------------------------------------------------------------------------
# compiler options for debug and release
# -----------------------------------------------------------------------------
#QMAKE_CXXFLAGS += -std=c++98

# optimization flag used in release builds (the -O2 is the default used by qmake)
QMAKE_CXXFLAGS_DEBUG += -fdiagnostics-show-option # to find out in gcc which option control warning
#QMAKE_CXXFLAGS_RELEASE += -O3 -ffast-math -msse3
#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE += -O0  # -ffast-math removed because of problems with NaNs
#QMAKE_CXXFLAGS_RELEASE += -g  # -ffast-math removed because of problems with NaNs
#QMAKE_STRIP=: # produces non-stripped (very large) libraries
#QMAKE_CXXFLAGS_RELEASE += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
#QMAKE_CXXFLAGS_RELEASE += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Werror -Wno-unused

# Eigen alighnment under windows, warnings from boost
win32{
    QMAKE_CXXFLAGS += -DEIGEN_DONT_ALIGN_STATICALLY=1 -mincoming-stack-boundary=2 -Wno-unused-local-typedefs -Wno-attributes -Wno-unknown-pragmas
#    QMAKE_CXXFLAGS += -D_MSC_VER=1301
#    QMAKE_CXXFLAGS += -DTYPENAME=typename
}

# Because of clang which knows nothing about unused_local_typedefs pragma
# TODO remove this by introducing clever macros in Macros.h
#macx|unix {
#    QMAKE_CXXFLAGS += -Wno-unused-local-typedefs
#}

# to compile with GPERFTOOLS support for code profiling
CONFIG(GPERFTOOLS) {
  QMAKE_CXXFLAGS += -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free
  LIBS += -L/opt/local/lib -lprofiler -ltcmalloc
}

CONFIG(PEDANTIC) {
  QMAKE_CXXFLAGS_RELEASE += -Weffc++
  QMAKE_CXXFLAGS_DEBUG += -Weffc++
}


# -----------------------------------------------------------------------------
# ROOT framework settings
# -----------------------------------------------------------------------------
macx|unix:ROOT_FRAMEWORK = $$system(root-config --prefix)
win32:ROOT_FRAMEWORK = "C:/root"

!isEmpty(ROOT_FRAMEWORK) {
  macx|unix {
    LIBEXT = so
  }
  win32 {
    LIBEXT = lib
  }

  macx|unix {
    ROOT_INCLUDE_DIR += $$system(root-config --incdir)
  }
  win32 {
    ROOT_INCLUDE_DIR += "C:/root/include"
  }
  MYROOTCINT = $${ROOT_FRAMEWORK}/bin/rootcint
  macx|unix {
    ROOTLIBDIR = $$system(root-config --libdir)
  }
  win32 {
    ROOTLIBDIR = "C:/root/lib"
  }
  ROOT_LIBRARY += -L$${ROOTLIBDIR}
  REQUIRED_ROOT_LIBS = Gui Core Cint RIO Hist Graf Graf3d Gpad Tree Rint Postscript Matrix MathCore Minuit2 Thread

  # check existence of required ROOT libraries
  for(x, REQUIRED_ROOT_LIBS) {
    libfile = $${ROOTLIBDIR}/lib$${x}.$${LIBEXT}
    !exists($${libfile}) : MISSED_ROOT_LIBRARIES += $${libfile}
    ROOT_LIBRARY += $${libfile}
  }
  !isEmpty(MISSED_ROOT_LIBRARIES): error( "The following libraries are missing in $${ROOTLIBDIR}: $${MISSED_ROOT_LIBRARIES}.")

  ROOT_LIBRARY += -lpthread -lm #-ldl

  # generation of ROOT dictionaries
  !isEmpty(BORNAGAIN_ROOT_DICT_FOR_CLASSES) {
    ROOT_CINT_TARGET = $${TARGET}
    SOURCES *= src/$${ROOT_CINT_TARGET}Dict.cpp
    rootcint.target = src/$${ROOT_CINT_TARGET}Dict.cpp
    rootcint.commands += $$MYROOTCINT
    rootcint.commands +=  -f $$rootcint.target  -c  -I$$BORNAGAIN_ROOT_DICT_INCLUDES $$BORNAGAIN_ROOT_DICT_FOR_CLASSES
    rootcint.depends = $$BORNAGAIN_ROOT_DICT_FOR_CLASSES
    rootcintecho.commands = @echo "Generating dictionary $$rootcint.target for $$BORNAGAIN_ROOT_DICT_FOR_CLASSES classes"
    QMAKE_EXTRA_TARGETS += rootcintecho rootcint
    QMAKE_CLEAN +=  src/$${ROOT_CINT_TARGET}Dict.cpp src/$${ROOT_CINT_TARGET}Dict.h
  }
}


# -----------------------------------------------------------------------------
# add python API support
# -----------------------------------------------------------------------------
macx|unix: WhichPython=$$system(which python)
win32:WhichPython="C:/Python27/python.exe"
!isEmpty(WhichPython) {
  pythonvers=$$system("$${WhichPython} -c \"import sys; sys.stdout.write(sys.version[:3])\" ")
  pythonnumpy=$$system("$${WhichPython} -c \"import sys; import numpy; sys.stdout.write(numpy.get_include())\" ")
  macx|unix {
    pythonsysincdir=$$system("$${WhichPython} -c \"import sys; sys.stdout.write(sys.prefix + \'/include/python\' + sys.version[:3])\" ")
    pythonsyslibdir=$$system("$${WhichPython} -c \"import sys; sys.stdout.write(sys.prefix + \'/lib\' )\" ")
  }
  win32 {
    pythonsysincdir=$$system("$${WhichPython} -c \"import sys; sys.stdout.write(sys.prefix + \'/include')\" ")
    pythonsyslibdir=$$system("$${WhichPython} -c \"import sys; sys.stdout.write(sys.prefix + \'/libs\' )\" ")
  }
  #message(pythonvers : $$pythonvers)
  #message(pythoninc  : $$pythonsysincdir)
  #message(pythonlib  : $$pythonsyslibdir)
  #message(pythonnumpy: $$pythonnumpy)
  lessThan(pythonvers, 2.6): error("BornAgain requires python 2.6 or greater")

  #INCLUDEPATH += $$pythonsysincdir
  macx|unix {
    PYTHON_LIB_DIRECTIVE=-lpython$$pythonvers
  }
  win32 {
    PYTHON_LIB_DIRECTIVE="-lpython27"
  }
  #LIBS += -lboost_python$${BOOST_LIB_SUFFIX} -L$$pythonsyslibdir $$PYTHON_LIB_DIRECTIVE

  # location of numpy
  !exists($$pythonnumpy/numpy/arrayobject.h): error("Can't find numpy/arrayobject.h in $$pythonnumpy, you have to install python-numpy-devel")
  #INCLUDEPATH += $$pythonnumpy
  PYTHON_INCLUDE_DIR = $$pythonsysincdir $$pythonnumpy
  PYTHON_LIBRARY = -lboost_python$${BOOST_LIB_SUFFIX} -L$$pythonsyslibdir $$PYTHON_LIB_DIRECTIVE
}
CONFIG(BORNAGAIN_PYTHON) {
    isEmpty(WhichPython): error("Can't find any sign of python")
}

# -----------------------------------------------------------------------------
# location of object files for debug/release builds
# -----------------------------------------------------------------------------
unix {
    CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/debug
    CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/release

    CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/.moc/debug
    CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/.moc/release

    RCC_DIR = $${OUT_PWD}/.rcc
    UI_DIR = $${OUT_PWD}/.uic
}

win32 {
    Release:DESTDIR = $${OUT_PWD}
    Debug:DESTDIR = $${OUT_PWD}
}



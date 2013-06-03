# -----------------------------------------------------------------------------
# checking common prerequisites
# -----------------------------------------------------------------------------
lessThan(QT_VERSION, 4.5) {
    error("BornAgain requires Qt 4.5 or greater")
}

!macx:!unix {
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
# general external libraries
# -----------------------------------------------------------------------------

# --- checking gsl header ---
GSL_HEADERFILE = gsl/gsl_sf_bessel.h
GSL_HEADER_LOCATIONS = /opt/local/include /usr/local/include /usr/include
for(dir, GSL_HEADER_LOCATIONS): isEmpty(GSL_INCLUDE): exists($${dir}/$${GSL_HEADERFILE}): GSL_INCLUDE = $${dir}
isEmpty(GSL_INCLUDE): message("Can't find" $${GSL_HEADERFILE} "in" $${GSL_HEADER_LOCATIONS})
GSL_LIB = $$replace(GSL_INCLUDE,"include","lib")
INCLUDEPATH *=  $${GSL_INCLUDE}
LIBS *= -L$${GSL_LIB}
LIBS += -lgsl -lgslcblas

# --- checking eigen headers ---
EIGEN_HEADERFILE = Eigen/Core
EIGEN_HEADER_LOCATIONS = /opt/local/include /opt/local/include/eigen3  /usr/local/include /usr/include
for(dir, EIGEN_HEADER_LOCATIONS): isEmpty(EIGEN_INCLUDE): exists($${dir}/$${EIGEN_HEADERFILE}): EIGEN_INCLUDE = $${dir}
isEmpty(EIGEN_INCLUDE): message("Can't find" $${EIGEN_HEADERFILE} "in" $${EIGEN_HEADER_LOCATIONS})
INCLUDEPATH *=  $${EIGEN_INCLUDE}

# --- checking fftw3 ---
FFTW3_HEADERFILE = fftw3.h
FFTW3_HEADER_LOCATIONS = /opt/local/include /usr/local/include /usr/include
for(dir, FFTW3_HEADER_LOCATIONS): isEmpty(FFTW3_INCLUDE): exists($${dir}/$${FFTW3_HEADERFILE}): FFTW3_INCLUDE = $${dir}
isEmpty(FFTW3_INCLUDE): message("Can't find" $${FFTW3_HEADERFILE} "in" $${FFTW3_HEADER_LOCATIONS})
FFTW3_LIB = $$replace(FFTW3_INCLUDE,"include","lib")
INCLUDEPATH *=  $${FFTW3_INCLUDE}
LIBS *= -L$${FFTW3_LIB}
LIBS += -lfftw3

# --- checking boost ---
BOOST_HEADERFILE = boost/version.hpp
BOOST_HEADER_LOCATIONS = /opt/local/include /usr/local/include /usr/include
for(dir, BOOST_HEADER_LOCATIONS): isEmpty(BOOST_INCLUDE): exists($${dir}/$${BOOST_HEADERFILE}): BOOST_INCLUDE = $${dir}
isEmpty(BOOST_INCLUDE): message("Can't find" $${BOOST_HEADERFILE} "in" $${BOOST_HEADER_LOCATIONS})
BOOST_LIBFILES = libboost*
BOOST_LIB_LOCATIONS = /opt/local/lib /usr/local/lib /usr/lib64 /usr/lib
for(dir, BOOST_LIB_LOCATIONS): isEmpty(BOOST_LIB) {
  NumberOfSuchFiles=$$system(ls $${dir}/$${BOOST_LIBFILES} 2> /dev/null | wc -l)
  !isEqual(NumberOfSuchFiles, 0): BOOST_LIB = $${dir}
}
isEmpty(BOOST_LIB): message("Can't find" $${BOOST_LIBFILES} "in" $${BOOST_LIB_LOCATIONS})
INCLUDEPATH *=  $${BOOST_INCLUDE}
LIBS *= -L$${BOOST_LIB}
LIBS += -lboost_program_options -lboost_iostreams -lboost_system -lboost_signals -lboost_filesystem -lboost_regex -lboost_thread
# checking special case when system doesn't have libboost_thread library but have libbost_thread-mt
NumberOfSuchFiles=$$system(ls $${BOOST_LIB}/libboost_thread-mt* 2> /dev/null | wc -l)
!isEqual(NumberOfSuchFiles, 0) {
  # library libboost_thread-mt exists
  LIBS = $$replace(LIBS, "-lboost_thread", "-lboost_thread-mt")
}

isEmpty(GSL_INCLUDE): error("missed dependency:" $${GSL_HEADERFILE})
isEmpty(FFTW3_INCLUDE): error("missed dependency:" $${FFTW3_HEADERFILE})
isEmpty(BOOST_INCLUDE): error("missed dependency:" $${BOOST_HEADERFILE})
isEmpty(BOOST_LIB): error("missed dependency:" $${BOOST_LIBFILES})


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
# general include paths
# -----------------------------------------------------------------------------
LOCATIONS = $$PWD/Core/Algorithms/inc \
            $$PWD/Core/Fitting/inc  \
            $$PWD/Core/FormFactors/inc  \
            $$PWD/Core/Geometry/inc  \
            $$PWD/Core/Samples/inc  \
            $$PWD/Core/Tools/inc

INCLUDEPATH += $${LOCATIONS}
DEPENDPATH  += $${LOCATIONS}


# -----------------------------------------------------------------------------
# compiler options for debug and release
# -----------------------------------------------------------------------------

# QMAKE_CXXFLAGS += -std=c++11 # not possible because of boost bugs
QMAKE_CXXFLAGS += -std=c++98

# optimization flag used in release builds (the -O2 is the default used by qmake)
QMAKE_CXXFLAGS_DEBUG += -fdiagnostics-show-option # to find out in gcc which option control warning
#QMAKE_CXXFLAGS_RELEASE += -O3 -ffast-math -msse3
#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE += -O0  # -ffast-math removed because of problems with NaNs
#QMAKE_CXXFLAGS_RELEASE += -g  # -ffast-math removed because of problems with NaNs
#QMAKE_STRIP=: # produces non-stripped (very large) libraries
#QMAKE_CXXFLAGS_RELEASE += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
#QMAKE_CXXFLAGS_RELEASE += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Werror -Wno-unused

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
# add ROOT libraries
# -----------------------------------------------------------------------------
CONFIG(BORNAGAIN_ROOT) {
    MYROOT = $$system(root-config --prefix)
    isEmpty(MYROOT): error("Could not run root-config. Install ROOT, and set PATH to include ROOTSYS/bin.")
    message("Found ROOT under directory " $${MYROOT})

    INCLUDEPATH += $$system(root-config --incdir)
    MYROOTCINT = $${MYROOT}/bin/rootcint
    ROOTLIBDIR = $$system(root-config --libdir)
    LIBS += -L$${ROOTLIBDIR}
    #REQUIRED_ROOT_LIBS = Cint Core EG Eve FTGL Ged Geom Graf Graf3d Gpad Gui Hist MathCore MathMore Matrix Minuit2 Physics Postscript RGL Rint RIO Thread Tree TreePlayer
    REQUIRED_ROOT_LIBS = Gui Core Cint RIO Hist Graf Graf3d Gpad Tree Rint Postscript Matrix MathCore MathMore Minuit2 Thread

    # check existence of required ROOT libraries
    for(x, REQUIRED_ROOT_LIBS) {
        libfile = $${ROOTLIBDIR}/lib$${x}.so
        !exists($${libfile}) : MISSED_ROOT_LIBRARIES += $${libfile}
        LIBS += -l$${x}
    }
    !isEmpty(MISSED_ROOT_LIBRARIES): error( "The following libraries are missing in $${ROOTLIBDIR}: $${MISSED_ROOT_LIBRARIES}.")

    LIBS += -lpthread -lm -ldl

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
#CONFIG  += BORNAGAIN_PYTHON
CONFIG(BORNAGAIN_PYTHON) {
  # user wants to compile python module
  WhichPython=$$system(which python)
  isEmpty(WhichPython) {
    # we do not have python
    error("Can not find any sign of python")
  } else {
    # we have python
    pythonvers=$$system("python -c 'import sys; sys.stdout.write(sys.version[:3])'")
    pythonsysincdir=$$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/include/python\" + sys.version[:3])'")
    #pythonsyslibdir=$$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/lib/python\" + sys.version[:3])'")
    pythonsyslibdir=$$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/lib\" )'")
    #message(we have python)
    #message($$pythonvers)
    #message($$pythonsysincdir)
    #message($$pythonsyslibdir)
    lessThan(pythonvers, 2.6): error("BornAgain requires python 2.6 or greater")
    INCLUDEPATH += $$pythonsysincdir
    #LIBS += -L$$pythonsyslibdir -lpython$$pythonvers -lboost_python
    LIBS += -lboost_python -L$$pythonsyslibdir -lpython$$pythonvers

    # we need to know the location of numpy
    pythonnumpy=$$system("python -c 'import sys; import numpy; sys.stdout.write(numpy.get_include())'")
    !exists($$pythonnumpy/numpy/arrayobject.h): error("Can't find numpy/arrayobject.h in $$pythonnumpy, you have to install python-numpy-devel")
    INCLUDEPATH += $$pythonnumpy
  }
}

# location of object files for debug/release builds
unix {
    CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/debug
    CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/release

    CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/.moc/debug
    CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/.moc/release

    RCC_DIR = $${OUT_PWD}/.rcc
    UI_DIR = $${OUT_PWD}/.uic
}

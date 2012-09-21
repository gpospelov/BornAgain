# common configuration for all packages

# -----------------------------------------------------------------------------
# checking common prerequisites
# -----------------------------------------------------------------------------
lessThan(QT_VERSION, 4.5) {
    error("GISASFW requires Qt 4.5 or greater")
}

!macx:!unix {
  error("Unknown operation system")
}


# -----------------------------------------------------------------------------
# to compile in debug mode
# -----------------------------------------------------------------------------
# CONFIG += debug


# -----------------------------------------------------------------------------
# general external libraries
# -----------------------------------------------------------------------------
#macx {
#  # we expect all libraries installed via macport
#  WHERE_TO_LOOK_PREFIX=/opt/local
#  INCLUDEPATH = /opt/local/include
#  LIBS = -L/opt/local/lib
#}
#!macx:unix{
#  WHERE_TO_LOOK_PREFIX=/usr/local
#  INCLUDEPATH = /usr/local/include
#  LIBS = -L/usr/local/lib -L/usr/lib64
#}

#educated guess about main directory with general libraries
exists(/opt/local/include/boost) {
    GENERAL_EXTERNALS_DIR = /opt/local
} else {
    exists(/usr/local/include/boost) {
        GENERAL_EXTERNALS_DIR = /usr/local
    } else {
        error("Neither of /usr/local/include/boost or /opt/local/include/boost exist")
    }
}

INCLUDEPATH = $${GENERAL_EXTERNALS_DIR}/include
LIBS = -L$${GENERAL_EXTERNALS_DIR}/lib

!macx:unix{
  LIBS += -L/usr/local/lib -L/usr/lib64
}

# adding libs we are depending on
LIBS += -lgsl -lgslcblas -lfftw3 -lboost_system -lboost_filesystem -lboost_regex -lboost_thread

# here is workaround since JCNS /usr/local doesn't have shared fftw3 (run with 'qmake CONFIG+=JCNS')
CONFIG(JCNS) {
  ##LIBS -= -lfftw3
  ##LIBS += -Bstatic -lfftw3f -Bdynamic
  ## "-lfftw3f" - with fPIC option, "-lfftw3" - without fPIC option
  #-Wl,--whole-archive
  #http://stackoverflow.com/questions/2763988/how-to-include-all-objects-of-an-archive-in-a-shared-object
  LIBS = -L/usr/users/jcns/pospelov/software/lib -L/usr/local/lib -L/usr/lib64 -lgsl -lgslcblas -lfftw3 -lboost_system -lboost_filesystem -lboost_regex -lboost_thread
}

# checking special case when system doesn't have libboost_thread library but have libbost_thread-mt
NumberOfSuchFiles=$$system(ls $${GENERAL_EXTERNALS_DIR}/lib/libboost_thread-mt* 2> /dev/null | wc -l)
!isEqual(NumberOfSuchFiles, 0) {
  # library libboost_thread-mt exists
  LIBS -= -lboost_thread
  LIBS += -lboost_thread-mt
} else {
  # library libboost_thread-mt doesn't exist, but may be libboost_thread exist?
  NumberOfSuchFiles=$$system(ls $${GENERAL_EXTERNALS_DIR}/lib/libboost_thread* 2> /dev/null | wc -l)
  isEqual(NumberOfSuchFiles, 0):error("Neither of libboost_thread or libboost_thread-mt have been found")
}


# -----------------------------------------------------------------------------
# options testing and performance issues
# -----------------------------------------------------------------------------

# optimization flag used in release builds (the -O2 is the default used by qmake)
# QMAKE_CXXFLAGS_RELEASE -= -O2
# QMAKE_CXXFLAGS_RELEASE += -O3

# uncommenting line below produces non-stripped (very large) libraries
#QMAKE_STRIP=:

# to compile with GPERFTOOLS support for code profiling
#CONFIG+=GPERFTOOLS
CONFIG(GPERFTOOLS) {
  QMAKE_CXXFLAGS += -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free
  LIBS += -L/opt/local/lib -lprofiler -ltcmalloc
}



# hints
# $${VAR} to access .pro variables, $$(VAR) to access environment variables




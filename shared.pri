# common configuration for all packages

lessThan(QT_VERSION, 4.5) {
    error("GISASFW requires Qt 4.5 or greater")
}

!macx:!unix {
  error("Unknown operation system")
}

# uncomment to compile with GPERFTOOLS support for code profiling
#CONFIG += GPERFTOOLS

# uncomment to compile in debug mode
#CONFIG += debug


## by default qmake is trying to strip library from unused symbols in non-debug mode, i.e. runs post-install 'strip' script on top of shared library
## this behaviour is causing problem, when this library later is used from python on linux session
## so, if you are on linux, have compiled library in non-debug mode, with python support, and then trying to import it in python, you will have problems
## lets forbid this behaviour
#QMAKE_STRIP=:


CONFIG(GPERFTOOLS) {
  QMAKE_CXXFLAGS += -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free
  LIBS += -L/opt/local/lib -lprofiler -ltcmalloc
}




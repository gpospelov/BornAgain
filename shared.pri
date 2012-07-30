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
CONFIG += debug

#
#QMAKE_STRIP=:


CONFIG(GPERFTOOLS) {
  QMAKE_CXXFLAGS += -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free
  LIBS += -L/opt/local/lib -lprofiler -ltcmalloc
}




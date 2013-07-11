AC_INIT([bornagain_core], [0:1], [http://apps.jcns.fz-juelich.de/BornAgain])

# standard configuration for shared libraries
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign subdir-objects]) # don't insert GNU blabla files
LT_INIT([disable-static])

AC_PROG_CXX
AC_SUBST(AM_CXXFLAGS,"-g -O2 -pedantic -Wall")
AC_CONFIG_HEADERS([config.h]) # to avoid endless -D options
AC_HEADER_STDC

# consistency check: is source code present?
AC_CONFIG_SRCDIR([Algorithms/Beam.cpp], [Samples/Samples.h])

# dependency checks

# make these Makefiles
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

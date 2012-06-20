###############################################################################
# qmake project file for google unit test library
###############################################################################
TARGET   = gtest
TEMPLATE = lib
CONFIG  += lib plugin
QT      -= gui core

QMAKE_EXTENSION_SHLIB = so

mygtest = gtest-1.6.0

INCLUDEPATH += $$mygtest/include
INCLUDEPATH += $$mygtest

SOURCES += \
    ./$$mygtest/src/gtest-all.cc

HEADERS += \
    ./$$mygtest/src/gtest-internal-inl.h

OBJECTS_DIR = obj

###############################################################################
# Installing library into dedicated directory at the end of compilation
###############################################################################
MYPREFIX = $$PWD/../.. # place to install library
target.path = $$MYPREFIX/lib
INSTALLS += target
##includes.files = $$mygtest/include/gtest/*.h
##includes.path = $$MYPREFIX/inc/gtest
#includes.files = $$mygtest/include/gtest
#includes.path = $$MYPREFIX/inc
#INSTALLS += includes
# there is a soft bug here in qmake, it looks like flag '-r' works
# only when it appears at the beginning of QMAKE_DISTCLEAN variable
# i.e. the order below is important
#QMAKE_DISTCLEAN += -r $$includes.path/gtest
QMAKE_DISTCLEAN += $$target.path/$(TARGET)

QMAKE_POST_LINK = (make install)


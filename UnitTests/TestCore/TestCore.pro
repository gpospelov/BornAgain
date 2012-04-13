QT       -= core
QT       -= gui

TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG -= app_bundle
CONFIG  += build_all

SOURCES += main.cpp

HEADERS += \
    NamedVectorTest.h \
    OutputDataTest.h

INCLUDEPATH += $$PWD/../../ThirdParty/gtest/include \
               $$PWD/../../Core/inc

OBJECTS_DIR = obj

LIBS += -L$$OUT_PWD/../../ThirdParty/gtest -lgtest
LIBS += -L$$OUT_PWD/../../Core -lCore

INCLUDEPATH += $$system($ROOTSYS/bin/root-config --incdir)
LIBS += $$system($ROOTSYS/bin/root-config --glibs)

# some hack that might be required for linux... under investigation
#LIBS += -lpthread
#LDFLAGS = -L/lib64
#QMAKE_CXXFLAGS += -pthread


PRE_TARGETDEPS += $$PWD/../../Core/libCore.dylib

# the projects depends from third party library "google test"
PRE_TARGETDEPS += $$PWD/../../ThirdParty/gtest/libgtest.a
makelibs.target = $$PWD/../../ThirdParty/gtest/libgtest.a
makelibs.commands = (cd $$PWD/../../ThirdParty/gtest; qmake; make)
makelibs.depends = FORCE
QMAKE_EXTRA_TARGETS += makelibs

# runs automatically tests right after linking
QMAKE_POST_LINK = ./$(TARGET)
